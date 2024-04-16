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
		Vector3 hitPos;					//�Փˍ��W�B
		Vector3 hitNormal;				//�@���B
		btCollisionObject* colObj;		//�R���W�����B
		Vector3 rayStart;				//���C�̎��_�B
		Vector3 rayEnd;					//���C�̏I�_�B
		bool isHit = false;				//�Փ˂������ǂ����B
		bool hitFraction = 1.0f;		//�Փˎ��ԁB

		btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{
			if (rayResult.m_hitFraction < hitFraction) {
				//������̂ق����߂��B
				hitPos.Lerp(rayStart, rayEnd, rayResult.m_hitFraction);
				//�@�����擾�B
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

		//���C���΂��B
		m_dynamicWorld->rayTest(start, end, callBack);

		//�Փ˂����Ȃ�B
		if (callBack.isHit) {
			hit.colObj = callBack.colObj;
			hit.position = callBack.hitPos;
			hit.normal = callBack.hitNormal;
			hit.fraction = callBack.hitFraction;
		}
		hit.isHit = callBack.isHit;

#ifdef _DEBUG
		//���C�̃f�o�b�O�\���B
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

		//�����G���W�����������B
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
		//�f�o�b�O���C���[�t���[�����������B
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
