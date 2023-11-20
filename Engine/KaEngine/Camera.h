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
		/// <param name="width"></param>
		/// <param name="height"></param>
		Camera(const float width, const float height, Shader* shader);

		~Camera();

		void Update();

		void Input();

	public:
		/// <summary>
		/// �ߕ��ʂ̐ݒ�B
		/// </summary>
		/// <param name=""></param>
		void SetNear(const float near)
		{
			m_near = near;
		}

		/// <summary>
		/// �����ʂ̐ݒ�B
		/// </summary>
		/// <param name=""></param>
		void SetFar(const float far)
		{
			m_far = far;
		}

		/// <summary>
		/// ����p��ݒ�B
		/// </summary>
		/// <param name="fov"></param>
		void SetFOV(const float fov)
		{
			m_fov = fov;
		}

	private:
		Shader*		m_shader = nullptr;		//�V�F�[�_�[�B
		Vector3		m_position;				//���W�B
		Vector3		m_forward;				//�O�����B
		Vector3		m_up;					//��B
		float		m_width = 0.0f;			//�����B
		float		m_height = 0.0f;		//�����B
		float		m_near = 0.1f;			//�ߕ��ʁB
		float		m_far = 1000.0f;		//�����ʁB
		float		m_fov = 90.0f;			//����p�B

		float		m_cameraSpeed = 0.0f;	//�J�������x�B
		float		m_sensitivity = 0.0f;	//�J�������x�B
	};
}