#pragma once
#include <functional>

namespace nsKaEngine {

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�}�l�[�W���[
	/// </summary>
	class GameObjectManager : Noncopyable
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		/// <summary>
		/// �C���X�^���X�̍쐬�B
		/// </summary>
		static void CreateInstance()
		{
			Ka_Assert(m_instance == nullptr, "codeError", "GameObjectManager�N���X�̃C���X�^���X�͈�������܂���B");
			m_instance = new GameObjectManager;
		}

		/// <summary>
		/// �C���X�^���X�̎擾�B
		/// </summary>
		/// <returns></returns>
		static GameObjectManager* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// �C���X�^���X�̍폜�B
		/// </summary>
		static void DeleteInstance()
		{
			m_instance->DeleteAllGameObjects();
			delete m_instance;
		}

	public:
		/// <summary>
		/// �X�V���������s�B
		/// </summary>
		void ExecuteUpdate();

		/// <summary>
		/// �`�揈�������s�B
		/// </summary>
		void ExecuteRender(RenderContext& rc);

		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̐����B
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
		/// �Q�[���I�u�W�F�N�g�̌����B
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
					//���O����v����Ȃ�B
					if (gameObject->IsMatchName(objectName) == true) {
						T* p = dynamic_cast<T*>(gameObject);
						return p;
					}
				}
			}
			return nullptr;
		}

		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̕��������B
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
					//���O����v����Ȃ�B
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
					//���O����v����Ȃ�B
					if (gameObject->IsMatchName(objectName) == true) {
						T* p = dynamic_cast<T*>(gameObject);
						//�N�G�����f�B
						if (func(p) == false) {
							return;
						}
					}
				}
			}
		}

		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̍폜�B
		/// </summary>
		/// <param name="gameObject"></param>
		void DestroyGameObject(GameObject* gameObject)
		{
			if (gameObject != nullptr) {
				gameObject->Destroy();
			}
		}

		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̑S�폜�B
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
		static GameObjectManager*			m_instance;					//�C���X�^���X�B
		typedef std::list<GameObject*>		GameObjectList;				//�Q�[���I�u�W�F�N�g�̃��X�g�B
		std::array<GameObjectList, 255>		m_gameObjectListArray;		//�Q�[���I�u�W�F�N�g�̃��X�g�t���z��B
	};

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̐����B
	/// </summary>
	/// <param name="priolity">�D��x</param>
	/// <param name="name">�I�u�W�F�N�g�̖��O</param>
	/// <returns></returns>
	template<class T>
	static inline T* Instantiate(const int priolity, const char* name)
	{
		return GameObjectManager::GetInstance()->InstantiateGameObject<T>(priolity, name);
	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̌����B
	/// </summary>
	/// <param name="name">�I�u�W�F�N�g�̖��O</param>
	/// <returns>���݂��Ȃ��Ȃ�nullptr</returns>
	template<class T>
	static inline T* Find(const char* name)
	{
		return GameObjectManager::GetInstance()->FindGameObject<T>(name);
	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̕��������B
	/// </summary>
	/// <param name="name">�I�u�W�F�N�g�̖��O</param>
	/// <returns>���݂��Ȃ��Ȃ�nullptr</returns>
	template<class T>
	static inline std::vector<T*>& Finds(const char* name)
	{
		return GameObjectManager::GetInstance()->FindGameObjects<T>(name);
	}

	/// <summary>
	/// �N�G�����g�p�����Q�[���I�u�W�F�N�g�̕��������B
	/// </summary>
	/// <param name="name">�Q�[���I�u�W�F�N�g�̖��O</param>
	/// <param name="func">�R�[���o�b�N�֐��Bfalse�Œ��f����</param>
	template<class T>
	static inline void Query(const char* name, std::function<bool(T* gameObject)> func)
	{
		return GameObjectManager::GetInstance()->QueryGameObject<T>(name, func);
	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̍폜�B
	/// </summary>
	/// <param name="gameObject">�j���������I�u�W�F�N�g</param>
	static inline void Destroy(GameObject* gameObject)
	{
		GameObjectManager::GetInstance()->DestroyGameObject(gameObject);
	}
}
