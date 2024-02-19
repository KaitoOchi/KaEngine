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
		/// �f�o�b�O�p�J�����̐؂�ւ��B
		/// </summary>
		void ToggleDebugCamera()
		{
			m_isActive = !m_isActive;
			m_position = g_camera3D->GetPosition();
			m_target = g_camera3D->GetTarget();
		}

	private:
		/// <summary>
		/// �ړ������B
		/// </summary>
		void Move();
		/// <summary>
		/// ��]�����B
		/// </summary>
		void Rotation();
		/// <summary>
		/// �J�[�\���̃��b�N�����B
		/// </summary>
		void CursorLock();

	private:
		Vector3			m_position;					//���W�B
		Vector3			m_target;					//�����_�B
		Vector2			m_rotSpeed;					//��]�p�x�B
		float			m_sensitivity = 0.05f;		//�J�������x�B
	};

}
