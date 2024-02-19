#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ゲームオブジェクトマネージャー
	/// </summary>
	class GameObjectManager : Noncopyable
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		/// <summary>
		/// インスタンスの作成。
		/// </summary>
		static void CreateInstance()
		{
			Ka_Assert(m_instance == nullptr, "codeError", "GameObjectManagerクラスのインスタンスは一つしか作れません。");
			m_instance = new GameObjectManager;
		}

		/// <summary>
		/// インスタンスの取得。
		/// </summary>
		/// <returns></returns>
		static GameObjectManager* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// インスタンスの削除。
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
		}

	public:
		/// <summary>
		/// 更新処理を実行。
		/// </summary>
		void ExecuteUpdate();

		/// <summary>
		/// 描画処理を実行。
		/// </summary>
		void ExecuteRender();

		template<class T>
		T* InstantiateGameObject(const int priolity, const char* objectName)
		{
			T* newObject = new T();
			newObject->SetName(objectName);
			m_gameObjectListArray.at(priolity).emplace_back(newObject);
			return newObject;
		}

		void DestroyGameObject(GameObject* gameObject)
		{
			if (gameObject != nullptr) {
				gameObject->Destroy();
			}
		}

	private:
		static GameObjectManager*			m_instance;					//インスタンス。
		typedef std::list<GameObject*>		GameObjectList;				//ゲームオブジェクトのリスト。
		std::array<GameObjectList, 255>		m_gameObjectListArray;		//ゲームオブジェクトのリスト付き配列。
	};

	template<class T>
	static inline T* Instantiate(const int priolity, const char* name)
	{
		return GameObjectManager::GetInstance()->InstantiateGameObject<T>(priolity, name);
	}

	static inline void Destroy(GameObject* gameObject)
	{
		GameObjectManager::GetInstance()->DestroyGameObject(gameObject);
	}
}

