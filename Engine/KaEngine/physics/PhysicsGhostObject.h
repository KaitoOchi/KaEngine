#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ゴーストオブジェクト。
	/// </summary>
	class PhysicsGhostObject : Noncopyable
	{
	public:
		PhysicsGhostObject();
		~PhysicsGhostObject();

		/// <summary>
		/// ボックスを作成。
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="size"></param>
		void CreareBox(
			const Vector3& pos,
			const Quaternion& rot,
			const Vector3 size
		);

		/// <summary>
		/// カプセルを作成。
		/// </summary>
		void CreateCapsule(
			const Vector3& pos,
			const Quaternion& rot,
			const float radius,
			const float height
		);

		/// <summary>
		/// 球体を作成。
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="radius"></param>
		void CreateSphere(
			const Vector3& pos,
			const Quaternion& rot,
			const float radius
		);

		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			btTransform trans = m_ghostObject.getWorldTransform();
			btVector3 vec = btVector3(pos.x, pos.y, pos.z);
			trans.setOrigin(vec);
		}

		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			btTransform trans = m_ghostObject.getWorldTransform();
			btQuaternion quat = btQuaternion(rot.x, rot.y, rot.z, rot.w);
			trans.setRotation(quat);
		}

		/// <summary>
		/// 開放処理。
		/// </summary>
		void Release()
		{
			if (m_isRegistPhysicsWorld == true) {
				PhysicsEngine::GetInstance()->RemoveCollisionObject(m_ghostObject);
				m_isRegistPhysicsWorld = false;
			}
		}

	private:
		/// <summary>
		/// 作成時の共通処理。
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		void CreateCommon(const Vector3& pos, const Quaternion& rot);

	private:
		btGhostObject						m_ghostObject;						//ゴーストオブジェクト。
		std::unique_ptr<btCollisionShape>	m_collider;							//コライダー。
		bool								m_isRegistPhysicsWorld = false;		//オブジェクトが登録されているかどうか。
	};
}
