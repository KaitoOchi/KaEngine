#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ボックスコライダー。
	/// </summary>
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider() {}
		~SphereCollider() {}

		/// <summary>
		/// 作成処理。
		/// </summary>
		/// <param name="size"></param>
		void Create(const float radius);

		/// <summary>
		/// 半径を取得。
		/// </summary>
		/// <returns></returns>
		const float GetRadius() const
		{
			return m_radius;
		}

		btCollisionShape* GetShape() const override
		{
			return m_shape.get();
		}

	private:
		std::unique_ptr<btSphereShape>		m_shape;
		float								m_radius;
	};
}

