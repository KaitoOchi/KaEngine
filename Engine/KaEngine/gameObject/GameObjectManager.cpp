#include "KaEnginePreCompile.h"
#include "GameObjectManager.h"

namespace nsKaEngine {

	GameObjectManager* GameObjectManager::m_instance = nullptr;

	GameObjectManager::GameObjectManager()
	{

	}

	GameObjectManager::~GameObjectManager()
	{

	}

	void GameObjectManager::ExecuteUpdate()
	{
		//�j���\��Ȃ炱����delete�B
		for (auto& gameObjectList : m_gameObjectListArray)
		{
			gameObjectList.remove_if([&](GameObject* gameObject){
				if (gameObject->IsDestroy()) {
					delete gameObject;
					return true;
				}
				return false;
			});
		}

		//Start�֐��̌Ăяo���B
		for (auto& gameObjectList : m_gameObjectListArray)
		{
			for (auto& gameObject : gameObjectList)
			{
				gameObject->StartWrapper();
			}
		}

		//Update�֐��̌Ăяo���B
		for (auto& gameObjectList : m_gameObjectListArray)
		{
			for (auto& gameObject : gameObjectList)
			{
				gameObject->UpdateWrapper();
			}
		}
	}

	void GameObjectManager::ExecuteRender()
	{
		//Render�֐��̌Ăяo���B
		for (auto& gameObjectList : m_gameObjectListArray)
		{
			for (auto& gameObject : gameObjectList)
			{
				gameObject->RenderWrapper();
			}
		}
	}
}