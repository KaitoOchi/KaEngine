#pragma once

namespace nsKaEngine {

	struct RigidbodyInitData
	{
		Vector3				pos;					//座標。
		Quaternion			rot;					//回転。
		ICollider*			collider = nullptr;		//コリジョン。
		float				mass = 0.0f;			//質量。
		float				restitution = 0.0f;		//反発力。
	};

	/// <summary>
	/// 剛体。
	/// </summary>
	class Rigidbody : Noncopyable
	{
	public:
		Rigidbody();
		~Rigidbody();

		/// <summary>
		/// 開放処理。
		/// </summary>
		void Release();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="initData"></param>
		void Init(const RigidbodyInitData& initData);

		/// <summary>
		/// 力を加える。
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
		/// 剛体を取得。
		/// </summary>
		/// <returns></returns>
		btRigidBody* GetRigidbody()
		{
			return m_rigidbody.get();
		}

	private:
		std::unique_ptr<btRigidBody>			m_rigidbody;	//剛体。
		std::unique_ptr<btDefaultMotionState>	m_motionState;	//モーションステート。
	};
}