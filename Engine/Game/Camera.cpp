#include "stdafx.h"
#include "Camera.h"

namespace nsKaEngine {

	Camera::Camera(const float width, const float height, Shader* shader)
	{
		m_width = width;
		m_height = height;

		m_shader = shader;

		m_position.y = 0.5f;
		m_position.z = -1.0f;
		m_forward.z = 1.0f;
		m_up.y = 1.0f;

		m_cameraSpeed = 0.0001f;
	}

	Camera::~Camera()
	{

	}

	void Camera::Update()
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(m_position.vec, m_position.vec + m_forward.vec, m_up.vec);
		projection = glm::perspective(glm::radians(m_fov), (float)(m_width / m_height), m_near, m_far);

		glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view));
	}

	void Camera::Input()
	{
		//if (Input::GetInstance()->GetKey(enButtonW)) {
		//	m_position += m_cameraSpeed * m_forward;
		//}

		//if (Input::GetInstance()->GetKey(enButtonA)) {
		//	m_position += m_cameraSpeed * Vector3(1.0f, 0.0f, 0.0f);
		//}

		//if (Input::GetInstance()->GetKey(enButtonS)) {
		//	m_position -= m_cameraSpeed * m_forward;
		//}

		//if (Input::GetInstance()->GetKey(enButtonD)) {
		//	m_position -= m_cameraSpeed * Vector3(1.0f, 0.0f, 0.0f);
		//}

		m_position.x += Input::GetInstance()->GetMouseAxis().x * m_cameraSpeed;
		m_position.y += Input::GetInstance()->GetMouseAxis().y * m_cameraSpeed;

		Vector3 mouse;
		mouse = Input::GetInstance()->GetMousePosition();

		float rotX = m_sensitivity * (mouse.x - (m_height / 2.0f)) / m_height;
		float rotY = m_sensitivity * (mouse.y - (m_height / 2.0f)) / m_height;
	}
}