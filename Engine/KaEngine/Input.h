#pragma once

namespace nsKaEngine{

	namespace
	{
		const int		INPUT_BIT_NUM_MAX = 8;				//BitFlag�̍ő�r�b�g���B
	}

	/// <summary>
	/// �L�[�R�[�h�B
	/// </summary>
	enum KeyCode
	{
		e_buttonSpace,
		e_buttonApostrophe,
		e_buttonComma,
		e_buttonMinus,
		e_buttonPeriod,
		e_buttonSlash,
		e_buttonBackSlash,
		e_buttonSemicolon,
		e_buttonEqual,
		e_buttonLeftBracket,
		e_buttonRightBracket,
		e_buttonGraveAccent,
		e_button0,
		e_button1,
		e_button2,
		e_button3,
		e_button4,
		e_button5,
		e_button6,
		e_button7,
		e_button8,
		e_button9,
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
		e_buttonEnter,
		e_buttonTab,
		e_buttonBackSpace,
		e_buttonRight,
		e_buttonLeft,
		e_buttonUp,
		e_buttonDown,
		e_buttonLeftShift,
		e_buttonRightShift,
		e_buttonLeftCtrl,
		e_buttonRightCtrl,
		e_buttonLeftAlt,
		e_buttonRightAlt,
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
		static void CreateInstance()
		{
			Ka_Assert(m_instance == nullptr, "codeError", "Input�N���X�̃C���X�^���X�͈�������܂���B");
			m_instance = new Input;
			m_instance->Init();
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
			return m_keyTriggerBit[static_cast<int>(code) / 8].IsSetFlag(static_cast<int>(code) % 8);
		}

		/// <summary>
		/// �{�^����������Ă��邩���擾�B
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKey(const KeyCode code) const
		{
			return m_keyPressBit[static_cast<int>(code) / 8].IsSetFlag(static_cast<int>(code) % 8);
		}

		/// <summary>
		/// �{�^���������ꂽ�u�Ԃ��擾�B
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKeyUp(const KeyCode code) const
		{
			return m_keyReleaseBit[static_cast<int>(code) / 8].IsSetFlag(static_cast<int>(code) % 8);
		}

		/// <summary>
		/// ��������̃{�^����������Ă��邩���擾�B
		/// </summary>
		/// <returns></returns>
		const bool GetAnyKey() const
		{
			for (auto& press : m_keyPressBit)
			{
				if (press.IsSetMaskFlagOR(BitFlag::All)) {
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
		const Vector2& GetMousePosition() const
		{
			return m_mousePosition;
		}

		/// <summary>
		/// �}�E�X�̓��͂��擾�B
		/// </summary>
		/// <returns>-1�`1�̊�</returns>
		const Vector2& GetMouseAxis() const
		{
			return m_mouseAxis;
		}

		/// <summary>
		/// �J�[�\�����Œ�ɂ���B
		/// </summary>
		void LockCursor()
		{
			glfwSetInputMode(GraphicsEngine::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			m_cursorLock = true;
		}

		/// <summary>
		/// �J�[�\���̌Œ�������B
		/// </summary>
		void UnLockCursor()
		{
			glfwSetInputMode(GraphicsEngine::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
		void Init();
		/// <summary>
		/// �L�[�̓��͏����B
		/// </summary>
		void InputKey(GLFWwindow* window);
		/// <summary>
		/// �}�E�X�̓��͏����B
		/// </summary>
		void InputMouse(GLFWwindow* window);

	private:
		static Input*	m_instance;							//�C���X�^���X�B
		Vector2			m_mousePosition;					//�}�E�X�̍��W�B
		Vector2			m_mouseAxis;						//�}�E�X�̓��́B
		BitFlag			m_keyTriggerBit[(static_cast<int>(e_buttonNum) / INPUT_BIT_NUM_MAX) + 1];	//�L�[�̃g���K�[����B
		BitFlag			m_keyPressBit[(static_cast<int>(e_buttonNum) / INPUT_BIT_NUM_MAX) + 1];		//�L�[�̃v���X����B
		BitFlag			m_keyReleaseBit[(static_cast<int>(e_buttonNum) / INPUT_BIT_NUM_MAX) + 1];	//�L�[�̃����[�X����B
		bool			m_mouseTrigger[e_mouseButtonNum];	//�}�E�X�̃g���K�[����B
		bool			m_mousePress[e_mouseButtonNum];		//�}�E�X�̃v���X����B
		bool			m_mouseRelease[e_mouseButtonNum];	//�}�E�X�̃����[�X����B
		bool			m_cursorLock = false;				//�J�[�\�����Œ肩�ǂ����B
	};
}

