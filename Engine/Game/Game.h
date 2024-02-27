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
	Player* m_player = nullptr;				//�v���C���[�B
	DebugCamera* m_debugCamera = nullptr;		//�f�o�b�O�J�����B
};

