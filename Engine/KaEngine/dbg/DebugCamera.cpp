#include "KaEnginePreCompile.h"
#include "DebugCamera.h"

namespace nsKaEngine {

	namespace
	{
		const float MOVE_SPEED = 3.0f;								//�ړ����x�B
		const float ANGLE_LIMIT = Mathf::PI / 2.0f - 0.001f;		//�p�x�̌��E�l�B
		const float TARGET_FORWARD = 10000.0f;						//�����_�̑O�����B
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

		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();

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

		//Space��Ctrl�ŏ㉺�B
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonSpace)) {
			moveSpeed.y += 1.0f;
		}
		if (Input::GetInstance()->GetKey(KeyCode::e_buttonLeftCtrl)) {
			moveSpeed.y -= 1.0f;
		}

		if (moveSpeed.LengthSq() < FLT_MIN) {
			return;
		}

		moveSpeed.Normalize();
		moveSpeed *= MOVE_SPEED;

		m_position += moveSpeed;

		g_camera3D->SetPosition(m_position);
	}

	void DebugCamera::Rotation()
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
		m_rotSpeed.x += -mouse.x * m_sensitivity;
		m_rotSpeed.y += -mouse.y * m_sensitivity;

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

	void DebugCamera::CursorLock()
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
}