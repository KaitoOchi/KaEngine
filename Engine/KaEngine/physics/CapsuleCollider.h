#pragma once

namespace nsKaEngine {

	/// <summary>
	/// カプセルコライダー。
	/// </summary>
	class CapsuleCollider : public ICollider
	{
	public:
		CapsuleCollider() {}
		~CapsuleCollider() {}

		/// <summary>
		/// 作成処理。
		/// </summary>
		/// <param name="radius"></param>
		/// <param name="height"></param>
		void Create(const float radius, const float height);

		/// <summary>
		/// 半径を取得。
		/// </summary>
		/// <returns></returns>
		const float GetRadius() const
		{
			return m_radius;
		}

		/// <summary>
		/// 高さを取得。
		/// </summary>
		/// <returns></returns>
		const float GetHeight() const
		{
			return m_height;
		}

		btCollisionShape* GetShape() const override
		{
			return m_shape.get();
		}

	private:
		std::unique_ptr<btCapsuleShape>		m_shape;
		float								m_radius = 0.0f;
		float								m_height = 0.0f;
	};
}

