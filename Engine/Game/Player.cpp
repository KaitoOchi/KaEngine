#include "stdafx.h"
#include "Player.h"


namespace
{
	const float MOVE_SPEED = 1.0f;								//移動速度。
	const float ANGLE_LIMIT = Mathf::PI / 2.0f - 0.001f;		//角度の限界値。
	const float TARGET_FORWARD = 10000.0f;						//注視点の前方向。
}

Player::Player()
{
	m_position = Vector3(50.0f, 50.0f, 50.0f);
	m_rotSpeed.x = Mathf::PI / 2.0f;
}

Player::~Player()
{

}

void Player::Update()
{
	Move();

	Rotation();

	g_camera3D->Update();

	if (Input::GetInstance()->GetCursorLock() == true) {

		if (Input::GetInstance()->GetKey(enButtonEsc)) {
			Input::GetInstance()->UnLockCursor();
		}
	}
	else {

		if (Input::GetInstance()->GetAnyMouseButton()) {
			Input::GetInstance()->LockCursor();
		}
	}
}

void Player::Move()
{
	Vector3 moveSpeed;

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	forward.y = 0.0f;
	right.y = 0.0f;

	//WASDで移動。
	if (Input::GetInstance()->GetKey(enButtonW)) {
		moveSpeed -= forward;
	}

	if (Input::GetInstance()->GetKey(enButtonA)) {
		moveSpeed -= right;
	}

	if (Input::GetInstance()->GetKey(enButtonS)) {
		moveSpeed += forward;
	}

	if (Input::GetInstance()->GetKey(enButtonD)) {
		moveSpeed += right;
	}

	moveSpeed.Normalize();
	moveSpeed *= MOVE_SPEED;

	m_position += moveSpeed;

	g_camera3D->SetPosition(m_position);
}

void Player::Rotation()
{
	if (Input::GetInstance()->GetCursorLock() == false) {
		return;
	}

	Vector3 mouse;
	mouse = Input::GetInstance()->GetMouseAxis();

	//スティックの入力を加算。
	m_rotSpeed.x += -mouse.x * m_sensitivity;
	m_rotSpeed.y += -mouse.y * m_sensitivity;

	//上下回転の限界値を範囲内に収める。
	m_rotSpeed.y = Mathf::Clamp(m_rotSpeed.y, -ANGLE_LIMIT, ANGLE_LIMIT);

	//注視点を回転させる。
	m_target.x = cos(m_rotSpeed.x) * cos(m_rotSpeed.y);
	m_target.y = sin(m_rotSpeed.y);
	m_target.z = sin(m_rotSpeed.x) * cos(m_rotSpeed.y);

	//注視点を正規化する。
	m_target.Normalize();
	//注視点を前方向に移動させる。
	m_target *= TARGET_FORWARD;
	//注視点をプレイヤーの方向に移動させる。
	m_target += m_position;

	g_camera3D->SetTarget(m_target);
}