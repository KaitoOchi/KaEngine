#pragma once

namespace nsKaEngine {

	struct RigidbodyInitData
	{
		Vector3				pos;					//���W�B
		Quaternion			rot;					//��]�B
		ICollider*			collider = nullptr;		//�R���W�����B
		float				mass = 0.0f;			//���ʁB
		float				restitution = 0.0f;		//�����́B
	};

	/// <summary>
	/// ���́B
	/// </summary>
	class Rigidbody : Noncopyable
	{
	public:
		Rigidbody();
		~Rigidbody();

		/// <summary>
		/// �J�������B
		/// </summary>
		void Release();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="initData"></param>
		void Init(const RigidbodyInitData& initData);

		/// <summary>
		/// �͂�������B
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="force"></param>
		void AddForce(const Vector3& pos, const Vector3& force)
		{
			btVector3 btPosition(pos.x, pos.y, pos.z);
			btVector3 btForce(force.x, force.y, force.z);
			m_rigidbody->applyForce(btForce, btPosition);
			m_rigidbody->activate();
		}

		/// <summary>
		/// ���̂��擾�B
		/// </summary>
		/// <returns></returns>
		btRigidBody* GetRigidbody()
		{
			return m_rigidbody.get();
		}

	private:
		std::unique_ptr<btRigidBody>			m_rigidbody;	//���́B
		std::unique_ptr<btDefaultMotionState>	m_motionState;	//���[�V�����X�e�[�g�B
	};
}