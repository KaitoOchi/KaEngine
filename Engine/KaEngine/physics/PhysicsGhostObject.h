#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �S�[�X�g�I�u�W�F�N�g�B
	/// </summary>
	class PhysicsGhostObject : Noncopyable
	{
	public:
		PhysicsGhostObject();
		~PhysicsGhostObject();

		/// <summary>
		/// �{�b�N�X���쐬�B
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
		/// �J�v�Z�����쐬�B
		/// </summary>
		void CreateCapsule(
			const Vector3& pos,
			const Quaternion& rot,
			const float radius,
			const float height
		);

		/// <summary>
		/// ���̂��쐬�B
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
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			btTransform trans = m_ghostObject.getWorldTransform();
			btVector3 vec = btVector3(pos.x, pos.y, pos.z);
			trans.setOrigin(vec);
		}

		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			btTransform trans = m_ghostObject.getWorldTransform();
			btQuaternion quat = btQuaternion(rot.x, rot.y, rot.z, rot.w);
			trans.setRotation(quat);
		}

		/// <summary>
		/// �J�������B
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
		/// �쐬���̋��ʏ����B
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		void CreateCommon(const Vector3& pos, const Quaternion& rot);

	private:
		btGhostObject						m_ghostObject;						//�S�[�X�g�I�u�W�F�N�g�B
		std::unique_ptr<btCollisionShape>	m_collider;							//�R���C�_�[�B
		bool								m_isRegistPhysicsWorld = false;		//�I�u�W�F�N�g���o�^����Ă��邩�ǂ����B
	};
}
