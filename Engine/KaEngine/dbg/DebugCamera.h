#pragma once

namespace nsKaEngine {

	class DebugCamera : public GameObject
	{
	public:
		DebugCamera();
		~DebugCamera();
		bool Start();
		void Update();

	public:
		/// <summary>
		/// デバッグ用カメラの切り替え。
		/// </summary>
		void ToggleDebugCamera()
		{
			m_isActive = !m_isActive;
			m_position = g_camera3D->GetPosition();
			m_target = g_camera3D->GetTarget();
		}

	private:
		/// <summary>
		/// 移動処理。
		/// </summary>
		void Move();
		/// <summary>
		/// 回転処理。
		/// </summary>
		void Rotation();
		/// <summary>
		/// カーソルのロック処理。
		/// </summary>
		void CursorLock();

	private:
		Vector3			m_position;					//座標。
		Vector3			m_target;					//注視点。
		Vector2			m_rotSpeed;					//回転角度。
		float			m_sensitivity = 0.05f;		//カメラ感度。
	};

}
