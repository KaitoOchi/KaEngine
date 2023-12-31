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
			m_rotation.Apply(m_forward);
			m_forward.Normalize();
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

		/// <summary>
		/// 前方向を設定。
		/// </summary>
		/// <param name="forward"></param>
		void SetForward(const Vector3& forward)
		{
			m_forward = forward;
			m_rotation.SetRotationFromVector(Vector3::AxisZ, m_forward);
		}

		/// <summary>
		/// 前方向を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetForward() const
		{
			return m_forward;
		}

		/// <summary>
		/// 上方向を設定。
		/// </summary>
		/// <param name="scale"></param>
		void SetUp(const Vector3& up)
		{
			m_up = up;
		}

		/// <summary>
		/// 上方向を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetUp() const
		{
			return m_up;
		}

		

	private:
		Vector3		m_position;
		Quaternion	m_rotation;
		Vector3		m_scale = Vector3::One;

		Vector3		m_forward = Vector3::Forward;
		Vector3		m_up = Vector3::Up;
	};


}