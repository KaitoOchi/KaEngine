#pragma once
class Player;
namespace nsKaEngine {
	class DebugCamera;
}

class Game : public GameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

private:
	Player* m_player = nullptr;				//プレイヤー。
	DebugCamera* m_debugCamera = nullptr;		//デバッグカメラ。
};

