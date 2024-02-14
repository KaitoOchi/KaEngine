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
		if (m_isNeedUpdate) {

			Vector2 windowSize = GraphicsEngine::GetInstance()->GetWindowSize();
			float aspect = (float)(windowSize.x / windowSize.y);

			//�J�����s����쐬�B
			m_viewMatrix.MakeLookAt(m_position, m_target, m_up);
			//�J�����s��̋t�s����v�Z�B
			m_viewMatrixInv.Inverse(m_viewMatrix);

			//�v���W�F�N�V�����s����쐬�B
			if (m_updateProjFunc == e_UpdateProjFunc_Prespective) {
				//�����ϊ��s����쐬�B
				m_projectionMatrix.MakeProjecionMatrix(m_fov, aspect, m_near, m_far);
			}
			else {
				//���s���e�s����쐬�B
				m_projectionMatrix.MakeOrthoProjectionMatrix(m_width, m_height, m_near, m_far);
			}
			//�v���W�F�N�V�����s��̋t�s����v�Z�B
			m_projectionMatrixInv.Inverse(m_projectionMatrix);
			//�r���[�v���W�F�N�V�����s����쐬�B
			m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
			//�r���[�v���W�F�N�V�����s��̋t�s����v�Z�B
			m_viewProjectionMatrixInv.Inverse(m_viewProjectionMatrix);

			//�E�����Ə������ݒ�B
			m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
			m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);

			m_isNeedUpdate = false;
		}
	}
}