#include "stdafx.h"
#include "Player.h"


namespace
{
	const float MOVE_SPEED = 500.0f;								//�ړ����x�B
	const float ANGLE_LIMIT = Mathf::PI / 2.0f - 0.001f;		//�p�x�̌��E�l�B
	const float TARGET_FORWARD = 10000.0f;						//�����_�̑O�����B
}

Player::Player()
{
	m_position = Vector3(0.0f, 50.0f, 250.0f);
	m_rotSpeed.x = Mathf::PI / 2.0f;

	g_camera3D->SetPosition(m_position);
	g_camera3D->SetTarget(Vector3::AxisZ * TARGET_FORWARD);
}

Player::~Player()
{

}

bool Player::Start()
{
	return true;
}

void Player::Update()
{
	Move();

	Rotation();

	g_camera3D->Update();

	CursorLock();
}

void Player::Move()
{
	Vector3 moveSpeed;

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	forward.y = 0.0f;
	right.y = 0.0f;

	//WASD�ňړ��B
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

	if (moveSpeed.LengthSq() < FLT_MIN) {
		return;
	}

	moveSpeed.Normalize();
	moveSpeed *= MOVE_SPEED * g_gameTime->GetFrameDeltaTime();

	m_position += moveSpeed;

	g_camera3D->SetPosition(m_position);
}

void Player::Rotation()
{
	if (Input::GetInstance()->GetCursorLock() == false) {
		return;
	}

	Vector2 mouse;
	mouse = Input::GetInstance()->GetMouseAxis();

	if (mouse.LengthSq() < FLT_MIN) {
		return;
	}
	
	//�X�e�B�b�N�̓��͂����Z�B
	m_rotSpeed.x += mouse.x * m_sensitivity * g_gameTime->GetFrameDeltaTime();
	m_rotSpeed.y += mouse.y * m_sensitivity * g_gameTime->GetFrameDeltaTime();

	//�㉺��]�̌��E�l��͈͓��Ɏ��߂�B
	m_rotSpeed.y = Mathf::Clamp(m_rotSpeed.y, -ANGLE_LIMIT, ANGLE_LIMIT);

	//�����_����]������B
	m_target.x = cos(m_rotSpeed.x) * cos(m_rotSpeed.y);
	m_target.y = sin(m_rotSpeed.y);
	m_target.z = sin(m_rotSpeed.x) * cos(m_rotSpeed.y);
	

	//�����_�𐳋K������B
	m_target.Normalize();
	//�����_��O�����Ɉړ�������B
	m_target *= TARGET_FORWARD;
	//�����_���v���C���[�̕����Ɉړ�������B
	m_target += m_position;

	g_camera3D->SetTarget(m_target);
}

void Player::CursorLock()
{
	if (Input::GetInstance()->GetCursorLock() == true) {
		//Esc�Ń��b�N�����B
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonEsc)) {
			Input::GetInstance()->UnLockCursor();
		}
	}
	else {
		//�N���b�N�Ń��b�N�B
		if (Input::GetInstance()->GetAnyMouseButton()) {
			Input::GetInstance()->LockCursor();
		}
	}
}

void Player::Render(RenderContext& rc)
{

}
