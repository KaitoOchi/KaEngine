#include "stdafx.h"
#include "Player.h"

void CreateWindow()
{

}

int main()
{
	//GLFWの初期化。
	glfwInit();

	//GLFWのバージョンとプロファイルを指定。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//ウィンドウを作成。
	GLFWwindow* window = glfwCreateWindow(static_cast<int>(FRAME_BUFFER_WIDTH), static_cast<int>(FRAME_BUFFER_HEIGHT), "Game", NULL, NULL);

	if (window == NULL) {
		std::cout << "GLFWのウィンドウ作成に失敗しました。" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	KaEngine::CreateInstance(window);

	g_camera3D = new Camera;
	g_camera3D->Init(KaEngine::GetInstance()->GetShader());

	Player* player = nullptr;
	player = new Player;


	//メインのループ処理。
	while (!glfwWindowShouldClose(window)) {

		KaEngine::GetInstance()->Execute();

		player->Update();
	}

	KaEngine::GetInstance()->DeleteInstance();

	//GLFWの終了処理。
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}