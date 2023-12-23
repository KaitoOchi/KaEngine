#include "KaEnginePreCompile.h"
#include "Camera.h"

namespace nsKaEngine {

	Camera::Camera()
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::Init()
	{
		m_target = m_forward * 10000.0f;
	}

	void Camera::Update()
	{
		float aspect = (float)(FRAME_BUFFER_WIDTH / FRAME_BUFFER_HEIGHT);

		if (m_isNeedUpdate) {
			//�J�����s����쐬�B
			m_viewMatrix.MakeLookAt(m_position, m_target, m_up);
			//�J�����s��̋t�s����v�Z�B
			m_viewMatrixInv.Inverse(m_viewMatrix);
			//�v���W�F�N�V�����s����쐬�B
			m_projectionMatrix.MakeProjecionMatrix(m_fov, aspect, m_near, m_far);
			//�v���W�F�N�V�����s��̋t�s����v�Z�B
			m_projectionMatrixInv.Inverse(m_projectionMatrix);

			//�E�����Ə������ݒ�B
			m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
			m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);

			//�r���[�v���W�F�N�V�����s����쐬�B
			m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
			//�r���[�v���W�F�N�V�����s��̋t�s����v�Z�B
			m_viewProjectionMatrixInv.Inverse(m_viewProjectionMatrix);

			m_isNeedUpdate = false;
		}
	}
}