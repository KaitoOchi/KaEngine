#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �����G���W���B
	/// </summary>
	class PhysicsEngine : Noncopyable
	{
	public:
		PhysicsEngine() {}
		~PhysicsEngine() {}

		/// <summary>
		/// �C���X�^���X�̍쐬�B
		/// </summary>
		static void CreateInstance()
		{
			Ka_Assert(m_instance == nullptr, "codeError", "PhysicsEngine�N���X�̃C���X�^���X�͈�������܂���B");
			m_instance = new PhysicsEngine;
			m_instance->Init();
		}

		/// <summary>
		/// �C���X�^���X�̎擾�B
		/// </summary>
		/// <returns></returns>
		static PhysicsEngine* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// �C���X�^���X�̍폜�B
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
		}

	private:
		/// <summary>
		/// �����������B
		/// </summary>
		void Init();
		/// <summary>
		/// ��������B
		/// </summary>
		void Release();

	private:
		static PhysicsEngine* m_instance;		//�C���X�^���X�B
		std::unique_ptr<btDefaultCollisionConfiguration> 	 m_collisionConfig;			//�f�t�H���g�̏Փˍ\���B
		std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;		//�Փˉ��������B
		std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//�R���X�g���C���g�\���o�[�B�S�������̉��������B
		std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;			//���[���h�B
#ifdef _DEBUG
		//DebugWireframe m_debugWireFrame;
		//bool m_isDrawDebugWireFrame = false;
#endif
	};

}
