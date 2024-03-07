#include "stdafx.h"
#include "system.h"

#include "Game.h"

int main()
{
	//�f�o�C�X�����擾�B
	DeviceInfo* deviceInfo = new DeviceInfo();
	GetDeviceInfo(deviceInfo);

	//�E�B���h�E���쐬�B
	GLFWwindow* window = nullptr;
	window = InitGLFW(
		window,
		"Game",
		deviceInfo
	);

	//���[�U�[��`�̃N���X�����B
	Game* game = Instantiate<Game>(0, "game");

	//���C���̃��[�v�����B
	while (!glfwWindowShouldClose(window)) {

		KaEngine::GetInstance()->BeginFrame();

		KaEngine::GetInstance()->Execute();

		GraphicsEngine::GetInstance()->Execute();

		KaEngine::GetInstance()->EndFrame();
	}

	KaEngine::GetInstance()->DeleteInstance();

	//GLFW�̏I�������B
	glfwDestroyWindow(window);
	glfwTerminate();

	delete deviceInfo;

	return 0;
}