#include "KaEnginePreCompile.h"
#include "PhysicsGhostObject.h"

namespace nsKaEngine {

	PhysicsGhostObject::PhysicsGhostObject()
	{

	}

	PhysicsGhostObject::~PhysicsGhostObject()
	{
		Release();
	}

	void PhysicsGhostObject::CreateCommon(const Vector3& pos, const Quaternion& rot)
	{
		m_ghostObject.setCollisionShape(m_collider->GetShape());

		btTransform btTrans;
		btTrans.setOrigin({ pos.x, pos.y, pos.z });
		btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
		m_ghostObject.setWorldTransform(btTrans);
		m_ghostObject.setCustomDebugColor(btVector3(0.0f, 1.0f, 0.0f));

		PhysicsEngine::GetInstance()->AddCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = true;
	}

	void PhysicsGhostObject::CreateBox(
		const Vector3& pos,
		const Quaternion& rot,
		const Vector3 size
	) {
		Release();

		auto collider = std::make_unique<BoxCollider>();
		collider->Create(size);
		m_collider = std::move(collider);

		CreateCommon(pos, rot);
	}

	void PhysicsGhostObject::CreateCapsule(
		const Vector3& pos,
		const Quaternion& rot,
		const float radius,
		const float height
	) {
		Release();

		auto collider = std::make_unique<CapsuleCollider>();
		collider->Create(radius, height);
		m_collider = std::move(collider);

		CreateCommon(pos, rot);
	}

	void PhysicsGhostObject::CreateSphere(
		const Vector3& pos,
		const Quaternion& rot,
		const float radius
	) {
		Release();

		auto collider = std::make_unique<SphereCollider>();
		collider->Create(radius);
		m_collider = std::move(collider);

		CreateCommon(pos, rot);
	}
}
