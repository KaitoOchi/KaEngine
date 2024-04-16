#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �����G���W���B
	/// </summary>
	class PhysicsEngine : Noncopyable
	{
	public:
		/// <summary>
		/// �Փˎ��̃f�[�^���i�[����\���́B
		/// </summary>
		struct RayHitObject
		{
			btCollisionObject* colObj;		//�R���W�����B
			Vector3 position;				//���W�B
			Vector3 normal;					//�@���B
			float fraction;					//�Փˎ��ԁB
			bool isHit;						//�Փ˂������ǂ����B
		};

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

	public:
		/// <summary>
		/// �R���W���������[���h�ɓo�^�B
		/// </summary>
		/// <param name="colliObj"></param>
		void AddCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->addCollisionObject(&colliObj);
		}

		/// <summary>
		/// �R���W���������[���h����폜�B
		/// </summary>
		/// <param name="colliObj"></param>
		void RemoveCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->removeCollisionObject(&colliObj);
		}

		/// <summary>
		/// ���C�e�X�g�B
		/// </summary>
		/// <param name="rayStart"></param>
		/// <param name="rayEnd"></param>
		/// <param name="hit"></param>
		void RayTest(
			const Vector3& rayStart,
			const Vector3& rayEnd,
			RayHitObject& hit
		);


		/// <summary>
		/// �J�n�����B
		/// </summary>
		void BeginFrame()
		{
#ifdef _DEBUG
			if (m_isDrawDebugWireFrame) {
				m_debugWireFrame.Begin();
			}
#endif
		}

		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update(const float deltaTime)
		{
			m_dynamicWorld->stepSimulation(deltaTime);
		}

		/// <summary>
		/// �I�������B
		/// </summary>
		void EndFrame()
		{
#ifdef _DEBUG
			if (m_isDrawDebugWireFrame) {
				m_dynamicWorld->debugDrawWorld();
				m_debugWireFrame.End();
			}
#endif
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
		static PhysicsEngine*								 m_instance;				//�C���X�^���X�B
		std::unique_ptr<btDefaultCollisionConfiguration> 	 m_collisionConfig;			//�f�t�H���g�̏Փˍ\���B
		std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;		//�Փˉ��������B
		std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//�R���X�g���C���g�\���o�[�B�S�������̉��������B
		std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;			//���[���h�B

#ifdef _DEBUG
		DebugWireFrame m_debugWireFrame;
		bool m_isDrawDebugWireFrame = true;
#endif


		btGhostObject m_btGhostObject;
		std::unique_ptr<btCollisionShape> m_shape;
	};

}
