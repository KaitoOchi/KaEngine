#pragma once

namespace nsKaEngine {

	//デバッグ用カメラ。
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
			m_target = Vector3::AxisZ;
			g_camera3D->SetTarget(m_target);
			g_camera3D->Update();
		}

	private:
		/// <summary>
		/// 移動処理。
		/// </summary>
		void Move();
		/// <summary>
		/// 移動入力処理。
		/// </summary>
		const bool IsInputWASD(Vector3& moveSpeed);
		/// <summary>
		/// マウスホイール入力処理。
		/// </summary>
		void InputMouseWheel();
		/// <summary>
		/// 回転処理。
		/// </summary>
		void Rotation();
		/// <summary>
		/// マウスカーソル入力処理。
		/// </summary>
		/// <returns></returns>
		const bool IsInputMouse(Vector2& mouse);
		/// <summary>
		/// 注視点の回転。
		/// </summary>
		void RotateTarget();
		/// <summary>
		/// カーソルのロック処理。
		/// </summary>
		void CursorLock();

	private:
		Vector3			m_position;					//座標。
		Vector3			m_target = Vector3::AxisZ;	//注視点。
		Vector3			m_rotSpeed;					//回転角度。
		float			m_sensitivity = 5.0f;		//カメラ感度。
		float			m_wheelSpeed = 1.0f;		//ホイール速度。
	};
}
