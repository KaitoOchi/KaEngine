#include "KaEnginePreCompile.h"
#include "Camera.h"

namespace nsKaEngine {

	Camera::Camera()
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::Init(Shader* shader)
	{
		m_shader = shader;

		m_target = m_forward * 10000.0f;
	}

	void Camera::Update()
	{
		float aspect = (float)(FRAME_BUFFER_WIDTH / FRAME_BUFFER_HEIGHT);

		m_viewMatrix.MakeLookAt(m_position, m_target, m_up);
		m_projectionMatrix.MakeProjecionMatrix(m_fov, aspect, m_near, m_far);

		m_viewMatrixInv.Inverse(m_viewMatrix);
		
		//‰E•ûŒü‚Æã•ûŒü‚ðÝ’èB
		m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
		m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);

		glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(m_projectionMatrix.mat * m_viewMatrix.mat));
	}
}