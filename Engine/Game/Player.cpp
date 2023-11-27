#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_position = Vector3(0.0f, 0.0f, 1.0f);
}

Player::~Player()
{

}

void Player::Update()
{
	Vector3 moveSpeed;

	//WASD‚ÅˆÚ“®B
	if (Input::GetInstance()->GetKey(enButtonW)) {
		moveSpeed -= g_camera3D->GetForward();
	}

	if (Input::GetInstance()->GetKey(enButtonA)) {
		moveSpeed -= g_camera3D->GetRight();
	}

	if (Input::GetInstance()->GetKey(enButtonS)) {
		moveSpeed += g_camera3D->GetForward();
	}

	if (Input::GetInstance()->GetKey(enButtonD)) {
		moveSpeed += g_camera3D->GetRight();
	}

	moveSpeed.Normalize();
	moveSpeed *= m_cameraSpeed;

	m_position += moveSpeed;

	Vector3 mouse;
	mouse = Input::GetInstance()->GetMouseAxis();

	//IJKL‚ÅƒJƒƒ‰‰ñ“]B
	if (Input::GetInstance()->GetKey(enButtonI)) {
		m_rotation.SetRotationDegX(m_sensitivity);
		g_camera3D->SetRotation(m_rotation);
	}
	if (Input::GetInstance()->GetKey(enButtonJ)) {
		m_rotation.SetRotationDegY(m_sensitivity);
		g_camera3D->SetRotation(m_rotation);
	}
	if (Input::GetInstance()->GetKey(enButtonK)) {
		m_rotation.SetRotationDegX(-m_sensitivity);
		g_camera3D->SetRotation(m_rotation);
	}
	if (Input::GetInstance()->GetKey(enButtonL)) {
		m_rotation.SetRotationDegY(-m_sensitivity);
		g_camera3D->SetRotation(m_rotation);
	}

	if (Input::GetInstance()->GetKey(enButtonEsc)) {
		Input::GetInstance()->UnLockCursor();
	}

	g_camera3D->SetPosition(m_position);
	g_camera3D->Update();
}