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
		//破棄予定ならここでdelete。
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

		//Start関数の呼び出し。
		for (auto& gameObjectList : m_gameObjectListArray)
		{
			for (auto& gameObject : gameObjectList)
			{
				gameObject->StartWrapper();
			}
		}

		//Update関数の呼び出し。
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
		//Render関数の呼び出し。
		for (auto& gameObjectList : m_gameObjectListArray)
		{
			for (auto& gameObject : gameObjectList)
			{
				gameObject->RenderWrapper();
			}
		}
	}
}