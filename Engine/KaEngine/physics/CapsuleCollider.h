#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �J�v�Z���R���C�_�[�B
	/// </summary>
	class CapsuleCollider : public ICollider
	{
	public:
		CapsuleCollider() {}
		~CapsuleCollider() {}

		/// <summary>
		/// �쐬�����B
		/// </summary>
		/// <param name="radius"></param>
		/// <param name="height"></param>
		void Create(const float radius, const float height);

		/// <summary>
		/// ���a���擾�B
		/// </summary>
		/// <returns></returns>
		const float GetRadius() const
		{
			return m_radius;
		}

		/// <summary>
		/// �������擾�B
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

