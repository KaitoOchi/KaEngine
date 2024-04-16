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
		btTransform btTrans;
		btTrans.setOrigin({ pos.x, pos.y, pos.z });
		btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
		m_ghostObject.setWorldTransform(btTrans);

		PhysicsEngine::GetInstance()->AddCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = true;
	}

	void PhysicsGhostObject::CreareBox(
		const Vector3& pos,
		const Quaternion& rot,
		const Vector3 size
	) {
		Release();

		std::unique_ptr<btBoxShape> shape = std::make_unique<btBoxShape>(btVector3(size.x, size.y, size.z));
		m_collider = std::move(shape);
		m_ghostObject.setCollisionShape(m_collider.get());
		m_ghostObject.setCustomDebugColor(btVector3(0.0f, 1.0f, 0.0f));

		CreateCommon(pos, rot);
	}

	void PhysicsGhostObject::CreateCapsule(
		const Vector3& pos,
		const Quaternion& rot,
		const float radius,
		const float height
	) {
		Release();

		std::unique_ptr<btCapsuleShape> shape = std::make_unique<btCapsuleShape>(radius, height);
		m_collider = std::move(shape);
		m_ghostObject.setCollisionShape(m_collider.get());
		m_ghostObject.setCustomDebugColor(btVector3(0.0f, 1.0f, 0.0f));

		CreateCommon(pos, rot);
	}

	void PhysicsGhostObject::CreateSphere(
		const Vector3& pos,
		const Quaternion& rot,
		const float radius
	) {
		Release();

		std::unique_ptr<btSphereShape> shape = std::make_unique<btSphereShape>(radius);
		m_collider = std::move(shape);
		m_ghostObject.setCollisionShape(m_collider.get());
		m_ghostObject.setCustomDebugColor(btVector3(0.0f, 1.0f, 0.0f));

		CreateCommon(pos, rot);
	}
}
