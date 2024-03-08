#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "dbg/DebugCamera.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Start()
{
	m_player = Instantiate<Player>(0, "player");

	m_debugCamera = Instantiate<nsKaEngine::DebugCamera>(0, "debugCamera");

	return true;
}

void Game::Update()
{
	if (Input::GetInstance()->GetKeyDown(e_buttonEqual)) {
		std::string command;
		std::cin >> command;
		if (command == "ToggleDebugCamera") {
			m_debugCamera->ToggleDebugCamera();
			m_player->ToggleActivate();
		}
	}
}
