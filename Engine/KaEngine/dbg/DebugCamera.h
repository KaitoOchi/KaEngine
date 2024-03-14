#pragma once

namespace nsKaEngine {

	//�f�o�b�O�p�J�����B
	class DebugCamera : public GameObject
	{
	public:
		DebugCamera();
		~DebugCamera();
		bool Start();
		void Update();

	public:
		/// <summary>
		/// �f�o�b�O�p�J�����̐؂�ւ��B
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
		/// �ړ������B
		/// </summary>
		void Move();
		/// <summary>
		/// �ړ����͏����B
		/// </summary>
		const bool IsInputWASD(Vector3& moveSpeed);
		/// <summary>
		/// �}�E�X�z�C�[�����͏����B
		/// </summary>
		void InputMouseWheel();
		/// <summary>
		/// ��]�����B
		/// </summary>
		void Rotation();
		/// <summary>
		/// �}�E�X�J�[�\�����͏����B
		/// </summary>
		/// <returns></returns>
		const bool IsInputMouse(Vector2& mouse);
		/// <summary>
		/// �����_�̉�]�B
		/// </summary>
		void RotateTarget();
		/// <summary>
		/// �J�[�\���̃��b�N�����B
		/// </summary>
		void CursorLock();

	private:
		Vector3			m_position;					//���W�B
		Vector3			m_target = Vector3::AxisZ;	//�����_�B
		Vector3			m_rotSpeed;					//��]�p�x�B
		float			m_sensitivity = 5.0f;		//�J�������x�B
		float			m_wheelSpeed = 1.0f;		//�z�C�[�����x�B
	};
}
