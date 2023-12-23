#include "stdafx.h"
#include "Player.h"

GLFWwindow* CreateGLFWWindow(GLFWwindow* window)
{
	//GLFW�̏������B
	glfwInit();

	//GLFW�̃o�[�W�����ƃv���t�@�C�����w��B
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�E�B���h�E���쐬�B
	window = glfwCreateWindow(static_cast<int>(FRAME_BUFFER_WIDTH), static_cast<int>(FRAME_BUFFER_HEIGHT), "Game", NULL, NULL);

	if (window == NULL) {
		std::cout << "GLFW�̃E�B���h�E�쐬�Ɏ��s���܂����B" << std::endl;
		glfwTerminate();
		std::abort();
	}
	glfwMakeContextCurrent(window);

	gladLoadGL(glfwGetProcAddress);
	glViewport(0, 0, static_cast<int>(FRAME_BUFFER_WIDTH), static_cast<int>(FRAME_BUFFER_HEIGHT));

	KaEngine::CreateInstance(window);

	return window;
}

int main()
{
	//�E�B���h�E���쐬�B
	GLFWwindow* window = nullptr;
	window = CreateGLFWWindow(window);

	Player* player = nullptr;
	player = new Player;


	//���C���̃��[�v�����B
	while (!glfwWindowShouldClose(window)) {

		KaEngine::GetInstance()->BeginFrame();

		KaEngine::GetInstance()->Execute();

		player->Update();

		KaEngine::GetInstance()->EndFrame();
	}

	KaEngine::GetInstance()->DeleteInstance();

	//GLFW�̏I�������B
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}