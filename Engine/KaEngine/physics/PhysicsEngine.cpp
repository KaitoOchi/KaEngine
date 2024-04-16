#include "KaEnginePreCompile.h"
#include "PhysicsEngine.h"

namespace nsKaEngine {

	namespace
	{
		const float DEFAULT_GRAVITY = -9.81f;
	}

	PhysicsEngine* PhysicsEngine::m_instance = nullptr;

	struct RayResultCallBack : public btCollisionWorld::RayResultCallback
	{
		Vector3 hitPos;					//衝突座標。
		Vector3 hitNormal;				//法線。
		btCollisionObject* colObj;		//コリジョン。
		Vector3 rayStart;				//レイの視点。
		Vector3 rayEnd;					//レイの終点。
		bool isHit = false;				//衝突したかどうか。
		bool hitFraction = 1.0f;		//衝突時間。

		btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{
			if (rayResult.m_hitFraction < hitFraction) {
				//こちらのほうが近い。
				hitPos.Lerp(rayStart, rayEnd, rayResult.m_hitFraction);
				//法線を取得。
				hitNormal.x = rayResult.m_hitNormalLocal.getX();
				hitNormal.y = rayResult.m_hitNormalLocal.getY();
				hitNormal.z = rayResult.m_hitNormalLocal.getZ();
				colObj = const_cast<btCollisionObject*>(rayResult.m_collisionObject);
			}
			isHit = true;
			return rayResult.m_hitFraction;
		}
	};

	void PhysicsEngine::RayTest(
		const Vector3& rayStart,
		const Vector3& rayEnd,
		RayHitObject& hit
	) {
		btVector3 start, end;
		start.setValue(rayStart.x, rayStart.y, rayStart.z);
		end.setValue(rayEnd.x, rayEnd.y, rayEnd.z);

		RayResultCallBack callBack;
		callBack.rayStart = rayStart;
		callBack.rayEnd = rayEnd;

		//レイを飛ばす。
		m_dynamicWorld->rayTest(start, end, callBack);

		//衝突したなら。
		if (callBack.isHit) {
			hit.colObj = callBack.colObj;
			hit.position = callBack.hitPos;
			hit.normal = callBack.hitNormal;
			hit.fraction = callBack.hitFraction;
		}
		hit.isHit = callBack.isHit;

#ifdef _DEBUG
		//レイのデバッグ表示。
		m_debugWireFrame.drawLine(start, end, btVector3(1.0f, 0.0f, 0.0f));
#endif
	}

	void PhysicsEngine::Release()
	{
		m_dynamicWorld.reset();
		m_constraintSolver.reset();
		m_constraintSolver.reset();
		m_overlappingPairCache.reset();
		m_collisionDispatcher.reset();
		m_collisionConfig.reset();
	}

	void PhysicsEngine::Init()
	{
		Release();

		//物理エンジンを初期化。
		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		m_collisionConfig = std::make_unique<btDefaultCollisionConfiguration>();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		m_collisionDispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfig.get());

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		m_constraintSolver = std::make_unique<btSequentialImpulseConstraintSolver>();

		m_dynamicWorld = std::make_unique<btDiscreteDynamicsWorld>(
			m_collisionDispatcher.get(),
			m_overlappingPairCache.get(),
			m_constraintSolver.get(),
			m_collisionConfig.get()
		);

		m_dynamicWorld->setGravity(btVector3(0, DEFAULT_GRAVITY, 0));

#ifdef _DEBUG
		//デバッグワイヤーフレームを初期化。
		m_debugWireFrame.Init();
		m_dynamicWorld->setDebugDrawer(&m_debugWireFrame);
#endif


		std::unique_ptr<btBoxShape> shape = std::make_unique<btBoxShape>(btVector3(10, 50, 10));
		m_shape = std::move(shape);
		m_btGhostObject.setCollisionShape(m_shape.get());
		m_btGhostObject.setCustomDebugColor(btVector3(0.0f, 1.0f, 0.0f));
		btTransform btTrans;
		btTrans.setOrigin({ 100, 150, 0 });
		btTrans.setRotation({ 0, 0, 0, 1 });
		m_btGhostObject.setWorldTransform(btTrans);
		AddCollisionObject(m_btGhostObject);
	}
}
