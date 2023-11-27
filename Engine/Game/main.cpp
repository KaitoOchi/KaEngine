#include "stdafx.h"
#include "Player.h"

void CreateWindow()
{

}

int main()
{
	//GLFW�̏������B
	glfwInit();

	//GLFW�̃o�[�W�����ƃv���t�@�C�����w��B
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�E�B���h�E���쐬�B
	GLFWwindow* window = glfwCreateWindow(static_cast<int>(FRAME_BUFFER_WIDTH), static_cast<int>(FRAME_BUFFER_HEIGHT), "Game", NULL, NULL);

	if (window == NULL) {
		std::cout << "GLFW�̃E�B���h�E�쐬�Ɏ��s���܂����B" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	KaEngine::CreateInstance(window);

	g_camera3D = new Camera;
	g_camera3D->Init(KaEngine::GetInstance()->GetShader());

	Player* player = nullptr;
	player = new Player;


	//���C���̃��[�v�����B
	while (!glfwWindowShouldClose(window)) {

		KaEngine::GetInstance()->Execute();

		player->Update();
	}

	KaEngine::GetInstance()->DeleteInstance();

	//GLFW�̏I�������B
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}