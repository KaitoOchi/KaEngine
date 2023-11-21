#pragma once

namespace nsKaEngine{

	/// <summary>
	/// �L�[�R�[�h�B
	/// </summary>
	enum KeyCode
	{
		enButtonW,
		enButtonA,
		enButtonS,
		enButtonD,
		enButtonEsc,
		enButtonNum,
	};

	/// <summary>
	/// �}�E�X�{�^���B
	/// </summary>
	enum MouseButton
	{
		enMouseButtonLeft,
		enMouseButtonRight,
		enMouseButtonMiddle,
		enMouseButtonNum,
	};


	/// <summary>
	/// ���̓N���X�B
	/// </summary>
	class Input : Noncopyable
	{
	public:
		Input();
		~Input();

		/// <summary>
		/// �C���X�^���X�𐶐��B
		/// </summary>
		static void CreateInstance(GLFWwindow* window)
		{
			if (m_instance != nullptr) {
				std::abort();
			}
			m_instance = new Input;
			m_instance->Init(window);
		}

		/// <summary>
		/// �C���X�^���X�̍폜�B
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
		}

		/// <summary>
		/// �C���X�^���X���擾�B
		/// </summary>
		/// <returns></returns>
		static Input* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="window"></param>
		void Init(GLFWwindow* window);

		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update();

	public:
		/// <summary>
		/// �{�^���������ꂽ�u�Ԃ��擾�B
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKeyDown(const KeyCode code) const
		{
			return m_keyTrigger[code];
		}

		/// <summary>
		/// �{�^����������Ă��邩���擾�B
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKey(const KeyCode code) const
		{
			return m_keyPress[code];
		}

		/// <summary>
		/// �{�^���������ꂽ�u�Ԃ��擾�B
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKeyUp(const KeyCode code) const
		{
			return m_keyRelease[code];
		}

		/// <summary>
		/// �}�E�X�{�^���������ꂽ�u�Ԃ��擾�B
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		const bool GetMouseButtonDown(const MouseButton button) const
		{
			return m_mouseTrigger[button];
		}

		/// <summary>
		/// �}�E�X�{�^����������Ă��邩���擾�B
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		const bool GetMouseButton(const MouseButton button) const
		{
			return m_mousePress[button];
		}

		/// <summary>
		/// �}�E�X�{�^���������ꂽ�u�Ԃ��擾�B
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		const bool GetMouseButtonUp(const MouseButton button) const
		{
			return m_mouseRelease[button];
		}

		/// <summary>
		/// �}�E�X�̍��W���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetMousePosition() const
		{
			return m_mousePosition;
		}

		/// <summary>
		/// �}�E�X�̓��͂��擾�B
		/// </summary>
		/// <returns>-1�`1�̊�</returns>
		const Vector3& GetMouseAxis() const
		{
			return m_mouseAxis;
		}

		/// <summary>
		/// �J�[�\�����Œ�ɂ���B
		/// </summary>
		void LockCursor()
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			m_cursorLock = true;
		}

		/// <summary>
		/// �J�[�\���̌Œ�������B
		/// </summary>
		void UnLockCursor()
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_cursorLock = false;
		}

		/// <summary>
		/// �J�[�\���̌Œ��Ԃ��擾�B
		/// </summary>
		/// <returns></returns>
		const bool GetCursorLock() const
		{
			return m_cursorLock;
		}

	private:
		/// <summary>
		/// �L�[�̓��͏����B
		/// </summary>
		void InputKey();
		/// <summary>
		/// �}�E�X�̓��͏����B
		/// </summary>
		void InputMouse();

	private:
		static Input*	m_instance;							//�C���X�^���X�B
		GLFWwindow*		m_window = nullptr;					//�E�B���h�E�B
		Vector3			m_mousePosition;					//�}�E�X�̍��W�B
		Vector3			m_mouseAxis;						//�}�E�X�̓��́B
		bool			m_keyTrigger[enButtonNum];			//�L�[�̃g���K�[����B
		bool			m_keyPress[enButtonNum];			//�L�[�̃v���X����B
		bool			m_keyRelease[enButtonNum];			//�L�[�̃����[�X����B
		bool			m_mouseTrigger[enMouseButtonNum];	//�}�E�X�̃g���K�[����B
		bool			m_mousePress[enMouseButtonNum];		//�}�E�X�̃v���X����B
		bool			m_mouseRelease[enMouseButtonNum];	//�}�E�X�̃����[�X����B
		bool			m_cursorLock = false;				//�J�[�\�����Œ肩�ǂ����B
	};
}

