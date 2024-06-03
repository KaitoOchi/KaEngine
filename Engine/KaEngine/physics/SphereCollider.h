#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �{�b�N�X�R���C�_�[�B
	/// </summary>
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider() {}
		~SphereCollider() {}

		/// <summary>
		/// �쐬�����B
		/// </summary>
		/// <param name="size"></param>
		void Create(const float radius);

		/// <summary>
		/// ���a���擾�B
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

