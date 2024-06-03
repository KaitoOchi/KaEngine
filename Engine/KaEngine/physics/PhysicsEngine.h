#pragma once

namespace nsKaEngine {

	/// <summary>
	/// 物理エンジン。
	/// </summary>
	class PhysicsEngine : Noncopyable
	{
	public:
		/// <summary>
		/// 衝突時のデータを格納する構造体。
		/// </summary>
		struct RayHitObject
		{
			btCollisionObject* colObj = nullptr;	//コリジョン。
			Vector3 position;						//座標。
			Vector3 normal;							//法線。
			float fraction = 0.0f;					//衝突時間。
			bool isHit = false;						//衝突したかどうか。
		};

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

	public:
		/// <summary>
		/// コリジョンをワールドに登録。
		/// </summary>
		/// <param name="colliObj"></param>
		void AddCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->addCollisionObject(&colliObj);
		}

		/// <summary>
		/// コリジョンをワールドから削除。
		/// </summary>
		/// <param name="colliObj"></param>
		void RemoveCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->removeCollisionObject(&colliObj);
		}

		/// <summary>
		/// 剛体をワールドに登録。
		/// </summary>
		/// <param name="rigidbody"></param>
		void AddRigidbody(btRigidBody& rigidbody)
		{
			m_dynamicWorld->addRigidBody(&rigidbody);
		}

		/// <summary>
		/// 剛体をワールドから削除。
		/// </summary>
		/// <param name="rigidbody"></param>
		void RemoveRigidbody(btRigidBody& rigidbody)
		{
			m_dynamicWorld->removeRigidBody(&rigidbody);
		}

		/// <summary>
		/// レイテスト。
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
		/// レイキャスト。
		/// </summary>
		/// <param name="rayStart"></param>
		/// <param name="rayEnd"></param>
		/// <param name="shape"></param>
		/// <param name="hit"></param>
		void RayCastHit(
			const Vector3& rayStart,
			const Vector3& rayEnd,
			btCollisionShape* shape,
			RayHitObject& hit
		);

		/// <summary>
		/// コンタクトテスト。
		/// </summary>
		/// <param name="colObj"></param>
		/// <param name="cb"></param>
		void ContactTest(
			btCollisionObject* colObj,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);

		void ConvexSweepTest(
			const btConvexShape* convexShape,
			const btTransform& from,
			const btTransform& to,
			btCollisionWorld::ConvexResultCallback& callback,
			btScalar allowedCcdPenetration = 0.0f
		) const {
			m_dynamicWorld->convexSweepTest(convexShape, from, to, callback, allowedCcdPenetration);
		}


		/// <summary>
		/// 開始処理。
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
		/// 更新処理。
		/// </summary>
		void Update(const float deltaTime)
		{
			m_dynamicWorld->stepSimulation(deltaTime);
		}

		/// <summary>
		/// 終了処理。
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
		/// 初期化処理。
		/// </summary>
		void Init();
		/// <summary>
		/// 解放処理。
		/// </summary>
		void Release();

	private:
		static PhysicsEngine*								 m_instance;				//インスタンス。
		std::unique_ptr<btDefaultCollisionConfiguration> 	 m_collisionConfig;			//デフォルトの衝突構成。
		std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;		//衝突解決処理。
		std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//ブロードフェーズ。衝突判定の枝切り。
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//コンストレイントソルバー。拘束条件の解決処理。
		std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;			//ワールド。

#ifdef _DEBUG
		DebugWireFrame m_debugWireFrame;
		bool m_isDrawDebugWireFrame = true;
#endif
	};

}
