#include "stdafx.h"
#include "system.h"

#include "Game.h"

int main()
{
	//デバイス情報を取得。
	DeviceInfo* deviceInfo = new DeviceInfo();
	GetDeviceInfo(deviceInfo);

	//ウィンドウを作成。
	GLFWwindow* window = nullptr;
	window = InitGLFW(
		window,
		"Game",
		deviceInfo
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

	delete deviceInfo;

	return 0;
}