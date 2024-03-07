#include "KaEnginePreCompile.h"
#include "DebugCamera.h"

namespace nsKaEngine {

	namespace
	{
		const Vector2	WHEEL_LIMIT = Vector2(0.01f, 3.0f);				//マウスホイール速度の限界値。
		const float		MOVE_SPEED = 500.0f;							//移動速度。
		const float		ANGLE_LIMIT = Mathf::PI / 2.0f - 0.001f;		//角度の限界値。
		const float		TARGET_FORWARD = 10000.0f;						//注視点の前方向。
	}

	DebugCamera::DebugCamera()
	{

	}

	DebugCamera::~DebugCamera()
	{

	}

	bool DebugCamera::Start()
	{
		m_isActive = false;

		return true;
	}

	void DebugCamera::Update()
	{
		Move();

		Rotation();

		g_camera3D->Update();

		CursorLock();
	}

	void DebugCamera::Move()
	{
		Vector3 moveSpeed;
		//移動の入力があるなら。
		if (IsInputWASD(moveSpeed) == true) {
			moveSpeed.Normalize();
			moveSpeed *= MOVE_SPEED * m_wheelSpeed * g_gameTime->GetFrameDeltaTime();
			m_position += moveSpeed;

			g_camera3D->SetPosition(m_position);
		}

		InputMouseWheel();
	}

	const bool DebugCamera::IsInputWASD(Vector3& moveSpeed)
	{
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();

		//WASDで移動。
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonW)) {
			moveSpeed -= forward;
		}
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonA)) {
			moveSpeed -= right;
		}
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonS)) {
			moveSpeed += forward;
		}
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonD)) {
			moveSpeed += right;
		}

		//SpaceとCtrlで上下。
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonSpace)) {
			moveSpeed.y += 1.0f;
		}
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonLeftCtrl)) {
			moveSpeed.y -= 1.0f;
		}

		//どれも押していないなら。
		if (moveSpeed.LengthSq() < FLT_MIN) {
			return false;
		}
		return true;
	}

	void DebugCamera::InputMouseWheel()
	{
		//マウスホイールで速度変更。
		m_wheelSpeed += (Input::GetInstance()->GetMouseWheel() / 10.0f);
		m_wheelSpeed = Mathf::Clamp(m_wheelSpeed, WHEEL_LIMIT.x, WHEEL_LIMIT.y);
	}

	void DebugCamera::Rotation()
	{
		if (Input::GetInstance()->GetCursorLock() == false) {
			return;
		}

		Vector2 mouseAxis;
		//回転の入力があるなら。
		if (IsInputMouse(mouseAxis) == true) {

			//スティックの入力を加算。
			m_rotSpeed.x += mouseAxis.x * m_sensitivity * g_gameTime->GetFrameDeltaTime();
			m_rotSpeed.y += mouseAxis.y * m_sensitivity * g_gameTime->GetFrameDeltaTime();
			//上下回転の限界値を範囲内に収める。
			m_rotSpeed.y = Mathf::Clamp(m_rotSpeed.y, -ANGLE_LIMIT, ANGLE_LIMIT);

			RotateTarget();

			//注視点を正規化する。
			m_target.Normalize();
			//注視点を前方向に移動させる。
			m_target *= TARGET_FORWARD;
			//注視点をプレイヤーの方向に移動させる。
			m_target += m_position;

			g_camera3D->SetTarget(m_target);
		}
	}

	const bool DebugCamera::IsInputMouse(Vector2& mouse)
	{
		mouse = Input::GetInstance()->GetMouseAxis();

		//マウスが移動していないなら。
		if (mouse.LengthSq() < FLT_MIN) {
			return false;
		}
		return true;
	}

	void DebugCamera::RotateTarget()
	{
		//注視点を回転させる。
		m_target.x = cos(m_rotSpeed.x) * cos(m_rotSpeed.y);
		m_target.y = sin(m_rotSpeed.y);
		m_target.z = sin(m_rotSpeed.x) * cos(m_rotSpeed.y);
	}

	void DebugCamera::CursorLock()
	{
		if (Input::GetInstance()->GetCursorLock() == true) {
			//Escでロック解除。
			if (Input::GetInstance()->GetKey(KeyCode::e_buttonEsc)) {
				Input::GetInstance()->UnLockCursor();
			}
		}
		else {
			//クリックでロック。
			if (Input::GetInstance()->GetAnyMouseButton()) {
				Input::GetInstance()->LockCursor();
			}
		}
	}
}
