#include "stdafx.h"
#include "system.h"

#include "Game.h"

int main()
{
	//デバイス情報を取得。
	Config* config = new Config();
	GetConfigFile(config);

	//ウィンドウを作成。
	GLFWwindow* window = nullptr;
	window = InitGLFW(
		window,
		"Game",
		config
	);

	//エンジンを初期化。
	KaEngine::CreateInstance(
		window,
		config
	);

	//ユーザー定義のクラス生成。
	Game* game = Instantiate<Game>(0, "game");

	//メインのループ処理。
	while (!glfwWindowShouldClose(window)) {

		KaEngine::GetInstance()->BeginFrame();

		KaEngine::GetInstance()->Execute();

		GraphicsEngine::GetInstance()->Execute();

		KaEngine::GetInstance()->EndFrame();
	}

	KaEngine::GetInstance()->DeleteInstance();

	//GLFWの終了処理。
	glfwDestroyWindow(window);
	glfwTerminate();

	delete config;

	return 0;
}