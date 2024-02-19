#pragma once

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
		static GameObjectManager*			m_instance;					//�C���X�^���X�B
		typedef std::list<GameObject*>		GameObjectList;				//�Q�[���I�u�W�F�N�g�̃��X�g�B
		std::array<GameObjectList, 255>		m_gameObjectListArray;		//�Q�[���I�u�W�F�N�g�̃��X�g�t���z��B
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

