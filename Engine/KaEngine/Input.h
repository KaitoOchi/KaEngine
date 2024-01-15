#pragma once

namespace nsKaEngine{

	/// <summary>
	/// �L�[�R�[�h�B
	/// </summary>
	enum KeyCode
	{
		e_buttonQ,
		e_buttonW,
		e_buttonE,
		e_buttonR,
		e_buttonT,
		e_buttonY,
		e_buttonU,
		e_buttonI,
		e_buttonO,
		e_buttonP,
		e_buttonA,
		e_buttonS,
		e_buttonD,
		e_buttonF,
		e_buttonG,
		e_buttonH,
		e_buttonJ,
		e_buttonK,
		e_buttonL,
		e_buttonZ,
		e_buttonX,
		e_buttonC,
		e_buttonV,
		e_buttonB,
		e_buttonN,
		e_buttonM,
		e_buttonEsc,
		e_buttonNum,
	};

	/// <summary>
	/// �}�E�X�{�^���B
	/// </summary>
	enum MouseButton
	{
		e_mouseButtonLeft,
		e_mouseButtonRight,
		e_mouseButtonMiddle,
		e_mouseButtonNum,
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
			Ka_Assert(m_instance == nullptr, "codeError", "Input�N���X�̃C���X�^���X�͈�������܂���B");
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
		/// ��������̃{�^����������Ă��邩���擾�B
		/// </summary>
		/// <returns></returns>
		const bool GetAnyKey() const
		{
			for (auto& press : m_keyPress)
			{
				if (press == true) {
					return true;
				}
			}
			return false;
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
		/// ��������̃}�E�X�{�^����������Ă��邩���擾�B
		/// </summary>
		/// <returns></returns>
		const bool GetAnyMouseButton() const
		{
			for (auto& mouseButton : m_mousePress)
			{
				if (mouseButton == true) {
					return true;
				}
			}
			return false;
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
		/// �����������B
		/// </summary>
		/// <param name="window"></param>
		void Init(GLFWwindow* window);
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
		bool			m_keyTrigger[e_buttonNum];			//�L�[�̃g���K�[����B
		bool			m_keyPress[e_buttonNum];			//�L�[�̃v���X����B
		bool			m_keyRelease[e_buttonNum];			//�L�[�̃����[�X����B
		bool			m_mouseTrigger[e_mouseButtonNum];	//�}�E�X�̃g���K�[����B
		bool			m_mousePress[e_mouseButtonNum];		//�}�E�X�̃v���X����B
		bool			m_mouseRelease[e_mouseButtonNum];	//�}�E�X�̃����[�X����B
		bool			m_cursorLock = false;				//�J�[�\�����Œ肩�ǂ����B
	};
}

