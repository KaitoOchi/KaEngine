#pragma once
#include <functional>

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
			m_instance->DeleteAllGameObjects();
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
		void ExecuteRender(RenderContext& rc);

		/// <summary>
		/// ゲームオブジェクトの生成。
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="priolity"></param>
		/// <param name="objectName"></param>
		/// <returns></returns>
		template<class T>
		T* InstantiateGameObject(const int priolity, const char* objectName)
		{
			T* newObject = new T();
			newObject->SetName(objectName);
			m_gameObjectListArray.at(priolity).emplace_back(newObject);
			return newObject;
		}

		/// <summary>
		/// ゲームオブジェクトの検索。
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="objectName"></param>
		/// <returns></returns>
		template<class T>
		T* FindGameObject(const char* objectName)
		{
			for (auto& gameObjectList : m_gameObjectListArray)
			{
				for (auto& gameObject : gameObjectList)
				{
					//名前が一致するなら。
					if (gameObject->IsMatchName(objectName) == true) {
						T* p = dynamic_cast<T*>(gameObject);
						return p;
					}
				}
			}
			return nullptr;
		}

		/// <summary>
		/// ゲームオブジェクトの複数検索。
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="objectName"></param>
		/// <returns></returns>
		template<class T>
		std::vector<T*>& FindGameObjects(const char* objectName)
		{
			static std::vector<T*> objectVec;
			objectVec.clear();
			for (auto& gameObjectList : m_gameObjectListArray)
			{
				for (auto& gameObject : gameObjectList)
				{
					//名前が一致するなら。
					if (gameObject->IsMatchName(objectName) == true) {
						T* p = dynamic_cast<T*>(gameObject);
						objectVec.emplace_back(p);
					}
				}
			}
			return objectVec;
		}

		template<class T>
		void QueryGameObject(const char* objectName, std::function<bool(T* gameObject)> func)
		{
			for (auto& gameObjectList : m_gameObjectListArray)
			{
				for (auto& gameObject : gameObjectList)
				{
					//名前が一致するなら。
					if (gameObject->IsMatchName(objectName) == true) {
						T* p = dynamic_cast<T*>(gameObject);
						//クエリ中断。
						if (func(p) == false) {
							return;
						}
					}
				}
			}
		}

		/// <summary>
		/// ゲームオブジェクトの削除。
		/// </summary>
		/// <param name="gameObject"></param>
		void DestroyGameObject(GameObject* gameObject)
		{
			if (gameObject != nullptr) {
				gameObject->Destroy();
			}
		}

		/// <summary>
		/// ゲームオブジェクトの全削除。
		/// </summary>
		void DeleteAllGameObjects()
		{
			for (auto gameObjects : m_gameObjectListArray)
			{
				for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
				{
					delete* itr;
				}
			}
		}

	private:
		static GameObjectManager*			m_instance;					//インスタンス。
		typedef std::list<GameObject*>		GameObjectList;				//ゲームオブジェクトのリスト。
		std::array<GameObjectList, 255>		m_gameObjectListArray;		//ゲームオブジェクトのリスト付き配列。
	};

	/// <summary>
	/// ゲームオブジェクトの生成。
	/// </summary>
	/// <param name="priolity">優先度</param>
	/// <param name="name">オブジェクトの名前</param>
	/// <returns></returns>
	template<class T>
	static inline T* Instantiate(const int priolity, const char* name)
	{
		return GameObjectManager::GetInstance()->InstantiateGameObject<T>(priolity, name);
	}

	/// <summary>
	/// ゲームオブジェクトの検索。
	/// </summary>
	/// <param name="name">オブジェクトの名前</param>
	/// <returns>存在しないならnullptr</returns>
	template<class T>
	static inline T* Find(const char* name)
	{
		return GameObjectManager::GetInstance()->FindGameObject<T>(name);
	}

	/// <summary>
	/// ゲームオブジェクトの複数検索。
	/// </summary>
	/// <param name="name">オブジェクトの名前</param>
	/// <returns>存在しないならnullptr</returns>
	template<class T>
	static inline std::vector<T*>& Finds(const char* name)
	{
		return GameObjectManager::GetInstance()->FindGameObjects<T>(name);
	}

	/// <summary>
	/// クエリを使用したゲームオブジェクトの複数検索。
	/// </summary>
	/// <param name="name">ゲームオブジェクトの名前</param>
	/// <param name="func">コールバック関数。falseで中断する</param>
	template<class T>
	static inline void Query(const char* name, std::function<bool(T* gameObject)> func)
	{
		return GameObjectManager::GetInstance()->QueryGameObject<T>(name, func);
	}

	/// <summary>
	/// ゲームオブジェクトの削除。
	/// </summary>
	/// <param name="gameObject">破棄したいオブジェクト</param>
	static inline void Destroy(GameObject* gameObject)
	{
		GameObjectManager::GetInstance()->DestroyGameObject(gameObject);
	}
}
