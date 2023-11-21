#pragma once

namespace nsKaEngine {

	/// <summary>
	/// 座標、回転、拡大クラス。
	/// </summary>
	class Transform : Noncopyable
	{
	public:
		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// 座標を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}

		/// <summary>
		/// 回転を取得。
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// 拡大率を設定。
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// 拡大率を取得。
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