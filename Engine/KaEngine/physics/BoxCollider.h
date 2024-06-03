#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �{�b�N�X�R���C�_�[�B
	/// </summary>
	class BoxCollider : public ICollider
	{
	public:
		BoxCollider() {}
		~BoxCollider() {}

		/// <summary>
		/// �쐬�����B
		/// </summary>
		/// <param name="size"></param>
		void Create(const Vector3& size);

		/// <summary>
		/// �T�C�Y���擾�B
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

