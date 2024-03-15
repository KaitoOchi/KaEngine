#include "KaEnginePreCompile.h"
#include "PhysicsEngine.h"

namespace nsKaEngine {

	PhysicsEngine* PhysicsEngine::m_instance = nullptr;

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

		m_dynamicWorld->setGravity(btVector3(0, -9.81f, 0));


		btBoxShape* shape = new btBoxShape(btVector3(10 / 2, 5 / 2, 7 / 2));

#ifdef _DEBUG
		//デバッグワイヤーフレームを初期化。
		//m_debugWireFrame.Init();
		//m_dynamicWorld->setDebugDrawer(&m_debugWireFrame);
#endif
	}
}