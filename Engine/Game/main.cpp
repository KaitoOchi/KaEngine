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

	PhysicsGhostObject boxGhostObject;
	boxGhostObject.CreateBox(
		Vector3(100.0f, 50.0f, 0.0f),
		Quaternion::Identity,
		Vector3(10.0f, 50.0f, 10.0f)
	);

	PhysicsGhostObject sphereGhostObject;
	sphereGhostObject.CreateSphere(
		Vector3(-150.0f, 50.0f, 0.0f),
		Quaternion::Identity,
		10.0f
	);

	Vector3 pos;
	float m_timer = 0.0f;

	//メインのループ処理。
	while (!glfwWindowShouldClose(window)) {

		KaEngine::GetInstance()->BeginFrame();

		KaEngine::GetInstance()->Execute();

		m_timer += g_gameTime->GetFrameDeltaTime();
		pos.x += m_timer;
		sphereGhostObject.SetPosition(pos);

		//PhysicsEngine::GetInstance()->ContactTest(&sphereGhostObject.GetbtCollisionObject(), [&](const btCollisionObject& contactObject) {
		//	if (sphereGhostObject.IsSelf(contactObject) == true) {
		//		pos = pos;
		//	}
		//});

		PhysicsEngine::RayHitObject hit;
		Vector3 start, end;
		start = g_camera3D->GetPosition();
		end = g_camera3D->GetPosition() + (g_camera3D->GetForward() * -1000.0f);
		PhysicsEngine::GetInstance()->RayCastHit(start, end, sphereGhostObject.GetbtCollisionShape(), hit);

		if (hit.isHit) {
			Vector3 a;
			a = hit.position;
		}

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