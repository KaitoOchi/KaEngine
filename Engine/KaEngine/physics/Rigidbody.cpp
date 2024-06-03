#include "KaEnginePreCompile.h"
#include "Rigidbody.h"

namespace nsKaEngine {

	Rigidbody::Rigidbody()
	{

	}

	Rigidbody::~Rigidbody()
	{
		Release();
	}

	void Rigidbody::Release()
	{
		if (m_rigidbody) {
			PhysicsEngine::GetInstance()->RemoveRigidbody(*this->GetRigidbody());
		}
	}

	void Rigidbody::Init(const RigidbodyInitData& initData)
	{
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(initData.pos.x, initData.pos.y, initData.pos.z));
		transform.setRotation(btQuaternion(initData.rot.x, initData.rot.y, initData.rot.z, initData.rot.w));

		m_motionState = std::make_unique<btDefaultMotionState>();
		m_motionState->setWorldTransform(transform);

		btVector3 btLocalInteria(0.0f, 0.0f, 0.0f);
		btCollisionShape* shape = initData.collider->GetShape();
		
		if (initData.mass != 0.0f) {
			shape->calculateLocalInertia(initData.mass, btLocalInteria);
		}

		btRigidBody::btRigidBodyConstructionInfo rigidbodyInfo(
			initData.mass,
			m_motionState.get(),
			shape,
			btLocalInteria
		);
		rigidbodyInfo.m_restitution = initData.restitution;

		m_rigidbody = std::make_unique<btRigidBody>(rigidbodyInfo);

		PhysicsEngine::GetInstance()->AddRigidbody(*this->GetRigidbody());
	}
}