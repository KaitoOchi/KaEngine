#pragma once
#include "ShaderClass.h"

namespace nsKaEngine {

	/// <summary>
	/// �J�����N���X�B
	/// </summary>
	class Camera
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		Camera();
		~Camera();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="shader"></param>
		void Init();

		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update();

	public:
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// ���W���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// �����_��ݒ�B
		/// </summary>
		/// <param name="target"></param>
		void SetTarget(const Vector3& target)
		{
			m_target = target;
			Quaternion rot;
			rot.SetRotationFromVector(Vector3::AxisZ, m_target);
			m_rotation = rot;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// �����_���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetTarget() const
		{
			return m_target;
		}

		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
			m_rotation.Apply(m_forward);
			m_forward.Normalize();
			m_target = m_forward * 50000.0f;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// ��]���擾�B
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// �O�������擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetForward() const
		{
			return m_forward;
		}

		/// <summary>
		/// ��������擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetUp() const
		{
			return m_up;
		}

		/// <summary>
		/// �E�������擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetRight() const
		{
			return m_right;
		}

		/// <summary>
		/// �ߕ��ʂ̐ݒ�B
		/// </summary>
		/// <param name=""></param>
		void SetNear(const float nearV)
		{
			m_near = nearV;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// �����ʂ̐ݒ�B
		/// </summary>
		/// <param name=""></param>
		void SetFar(const float farV)
		{
			m_far = farV;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// ����p��ݒ�B
		/// </summary>
		/// <param name="fov"></param>
		void SetFOV(const float fov)
		{
			m_fov = fov;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// �r���[�v���W�F�N�V�����s����擾�B
		/// </summary>
		/// <returns></returns>
		const Matrix& GetViewProjectionMatrix() const
		{
			return m_viewProjectionMatrix;
		}

	private:
		Vector3		m_position;						//���W�B
		Vector3		m_target;						//�����_�B
		Vector3		m_forward = Vector3::Forward;	//�O�����B
		Vector3		m_up = Vector3::Up;				//������B
		Vector3		m_right = Vector3::AxisX;		//�E�����B
		Quaternion	m_rotation;						//��]�B
		Matrix		m_viewMatrix;					//�r���[�s��B
		Matrix		m_viewMatrixInv;				//�r���[�s��̋t�s��B
		Matrix		m_projectionMatrix;				//�����ϊ��s��B
		Matrix		m_projectionMatrixInv;			//�����ϊ��s��̋t�s��B
		Matrix		m_viewProjectionMatrix;			//�r���[�v���W�F�N�V�����s��B
		Matrix		m_viewProjectionMatrixInv;		//�r���[�v���W�F�N�V�����s��̋t�s��B
		bool		m_isNeedUpdate = true;			//�X�V���K�v���ǂ����B
		float		m_near = 0.1f;					//�ߕ��ʁB
		float		m_far = 1000.0f;				//�����ʁB
		float		m_fov = 60.0f;					//����p�B
	};
}