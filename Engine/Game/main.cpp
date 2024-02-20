#include "stdafx.h"

#include "Player.h"
#include "dbg/DebugCamera.h"

GLFWwindow* CreateGLFWWindow(GLFWwindow* window)
{
	//GLFWの初期化。
	glfwInit();

	//GLFWのバージョンとプロファイルを指定。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//マルチサンプリングを有効。
	glfwWindowHint(GLFW_SAMPLES, 4);

	//ウィンドウを作成。
	window = glfwCreateWindow(
		static_cast<int>(FRAME_BUFFER_WIDTH),
		static_cast<int>(FRAME_BUFFER_HEIGHT),
		"Game",
		NULL,
		NULL
	);

	if (window == NULL) {
		std::cout << "GLFWのウィンドウ作成に失敗しました。" << std::endl;
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
	//ウィンドウを作成。
	GLFWwindow* window = nullptr;
	window = CreateGLFWWindow(window);

	Player* player = nullptr;
	player = Instantiate<Player>(0, "player");

	DebugCamera* debugCamera = nullptr;
	debugCamera = Instantiate<DebugCamera>(0, "debugCamera");


	//メインのループ処理。
	while (!glfwWindowShouldClose(window)) {

		KaEngine::GetInstance()->BeginFrame();

		KaEngine::GetInstance()->Execute();

		if (Input::GetInstance()->GetMouseButtonDown(e_mouseButtonRight)) {
			debugCamera->ToggleDebugCamera();
			player->ToggleActivate();
		}

		GraphicsEngine::GetInstance()->Execute();

		KaEngine::GetInstance()->EndFrame();
	}

	KaEngine::GetInstance()->DeleteInstance();

	//GLFWの終了処理。
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}