#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ボックスコライダー。
	/// </summary>
	class BoxCollider : public ICollider
	{
	public:
		BoxCollider() {}
		~BoxCollider() {}

		/// <summary>
		/// 作成処理。
		/// </summary>
		/// <param name="size"></param>
		void Create(const Vector3& size);

		/// <summary>
		/// サイズを取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetSize() const
		{
			return m_size;
		}

		btCollisionShape* GetShape() const override
		{
			return m_shape.get();
		}

	private:
		std::unique_ptr<btBoxShape>		m_shape;
		Vector3							m_size;
	};
}

