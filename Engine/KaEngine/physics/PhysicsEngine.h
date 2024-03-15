#pragma once

namespace nsKaEngine {

	/// <summary>
	/// 物理エンジン。
	/// </summary>
	class PhysicsEngine : Noncopyable
	{
	public:
		PhysicsEngine() {}
		~PhysicsEngine() {}

		/// <summary>
		/// インスタンスの作成。
		/// </summary>
		static void CreateInstance()
		{
			Ka_Assert(m_instance == nullptr, "codeError", "PhysicsEngineクラスのインスタンスは一つしか作れません。");
			m_instance = new PhysicsEngine;
			m_instance->Init();
		}

		/// <summary>
		/// インスタンスの取得。
		/// </summary>
		/// <returns></returns>
		static PhysicsEngine* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// インスタンスの削除。
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
		}

	private:
		/// <summary>
		/// 初期化処理。
		/// </summary>
		void Init();
		/// <summary>
		/// 解放処理。
		/// </summary>
		void Release();

	private:
		static PhysicsEngine* m_instance;		//インスタンス。
		std::unique_ptr<btDefaultCollisionConfiguration> 	 m_collisionConfig;			//デフォルトの衝突構成。
		std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;		//衝突解決処理。
		std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//ブロードフェーズ。衝突判定の枝切り。
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//コンストレイントソルバー。拘束条件の解決処理。
		std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;			//ワールド。
#ifdef _DEBUG
		//DebugWireframe m_debugWireFrame;
		//bool m_isDrawDebugWireFrame = false;
#endif
	};

}
