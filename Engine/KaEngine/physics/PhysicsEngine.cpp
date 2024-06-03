#include "KaEnginePreCompile.h"
#include "PhysicsEngine.h"

namespace nsKaEngine {

	namespace
	{
		const float DEFAULT_GRAVITY = -9.81f;
	}

	PhysicsEngine* PhysicsEngine::m_instance = nullptr;

	struct ContactResultCallBack : public btCollisionWorld::ContactResultCallback
	{
		using ContantTestCallback = std::function<void(const btCollisionObject& contactCollisionObject)>;
		ContantTestCallback  cb;
		btCollisionObject* colObj = nullptr;

		btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
		{
			if (colObj == colObj0Wrap->getCollisionObject()) {
				cb(*colObj0Wrap->getCollisionObject());
			}
			return 0.0f;
		}
	};

	struct ConvexResultCallBack : public btCollisionWorld::ConvexResultCallback
	{
		Vector3 hitPos;							//衝突座標。
		Vector3 hitNormal;						//法線。
		btCollisionObject* colObj = nullptr;	//コリジョン。
		Vector3 rayStart;						//レイの視点。
		Vector3 rayEnd;							//レイの終点。
		bool isHit = false;
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)


		{
			isHit = true;
			return 0.0f;
		}
	};

	struct RayResultCallBack : public btCollisionWorld::RayResultCallback
	{
		Vector3 hitPos;							//衝突座標。
		Vector3 hitNormal;						//法線。
		btCollisionObject* colObj = nullptr;	//コリジョン。
		Vector3 rayStart;						//レイの視点。
		Vector3 rayEnd;							//レイの終点。
		bool isHit = false;						//衝突したかどうか。
		float hitFraction = 1.0f;				//衝突時間。

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

		RayResultCallBack callback;
		callback.rayStart = rayStart;
		callback.rayEnd = rayEnd;

		//レイを飛ばす。
		m_dynamicWorld->rayTest(start, end, callback);

		//衝突したなら。
		if (callback.isHit) {
			hit.colObj = callback.colObj;
			hit.position = callback.hitPos;
			hit.normal = callback.hitNormal;
			hit.fraction = callback.hitFraction;
		}
		hit.isHit = callback.isHit;

#ifdef _DEBUG
		//レイのデバッグ表示。
		m_debugWireFrame.drawLine(start, end, btVector3(1.0f, 0.0f, 0.0f));
#endif
	}

	//todo
	void PhysicsEngine::RayCastHit(
		const Vector3& rayStart,
		const Vector3& rayEnd,
		btCollisionShape* shape,
		RayHitObject& hit
	) {
		btVector3 start, end;
		start.setValue(rayStart.x, rayStart.y, rayStart.z);
		end.setValue(rayEnd.x, rayEnd.y, rayEnd.z);

		btTransform startTrans, endTrans;
		startTrans.setIdentity();
		endTrans.setIdentity();
		startTrans.setOrigin(start);
		endTrans.setOrigin(end);

		ConvexResultCallBack callback;
		callback.rayStart = rayStart;
		callback.rayEnd = rayEnd;

		ConvexSweepTest((const btConvexShape*)shape, startTrans, endTrans, callback);

		if (callback.isHit) {
			hit.position = callback.hitPos;
			hit.normal = callback.hitNormal;
		}
	}

	void PhysicsEngine::ContactTest(
		btCollisionObject* colObj,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	) {
		ContactResultCallBack callback;
		callback.cb = cb;
		callback.colObj = colObj;
		m_dynamicWorld->contactTest(colObj, callback);
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
	}
}
