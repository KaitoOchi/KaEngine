#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ���W�A��]�A�g��N���X�B
	/// </summary>
	class Transform : Noncopyable
	{
	public:
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// ���W���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}

		/// <summary>
		/// ��]���擾�B
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// �g�嗦��ݒ�B
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// �g�嗦���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetScale () const
		{
			return m_scale;
		}

		

	private:
		Vector3		m_position;
		Quaternion	m_rotation;
		Vector3		m_scale = Vector3::One;

		Vector3		m_forward = Vector3::Forward;
		Vector3		m_up = Vector3::Up;
	};


}