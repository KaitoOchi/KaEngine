#pragma once

namespace nsKaEngine{

	namespace
	{
		const int		INPUT_BIT_NUM_MAX = 8;				//BitFlagの最大ビット数。
	}

	/// <summary>
	/// キーコード。
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
	/// マウスボタン。
	/// </summary>
	enum MouseButton
	{
		e_mouseButtonLeft,
		e_mouseButtonRight,
		e_mouseButtonMiddle,
		e_mouseButtonNum,
	};

	/// <summary>
	/// 入力クラス。
	/// </summary>
	class Input : Noncopyable
	{
	public:
		Input();
		~Input();

		/// <summary>
		/// インスタンスを生成。
		/// </summary>
		static void CreateInstance()
		{
			Ka_Assert(m_instance == nullptr, "codeError", "Inputクラスのインスタンスは一つしか作れません。");
			m_instance = new Input;
			m_instance->Init();
		}

		/// <summary>
		/// インスタンスの削除。
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
		}

		/// <summary>
		/// インスタンスを取得。
		/// </summary>
		/// <returns></returns>
		static Input* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// 更新処理。
		/// </summary>
		void Update();

	public:
		/// <summary>
		/// ボタンが押された瞬間を取得。
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKeyDown(const KeyCode code) const
		{
			return m_keyTriggerBit[static_cast<int>(code) / 8].IsSetFlag(static_cast<int>(code) % 8);
		}

		/// <summary>
		/// ボタンが押されているかを取得。
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKey(const KeyCode code) const
		{
			return m_keyPressBit[static_cast<int>(code) / 8].IsSetFlag(static_cast<int>(code) % 8);
		}

		/// <summary>
		/// ボタンが離された瞬間を取得。
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKeyUp(const KeyCode code) const
		{
			return m_keyReleaseBit[static_cast<int>(code) / 8].IsSetFlag(static_cast<int>(code) % 8);
		}

		/// <summary>
		/// 何かしらのボタンが押されているかを取得。
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
		/// マウスボタンが押された瞬間を取得。
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		const bool GetMouseButtonDown(const MouseButton button) const
		{
			return m_mouseTrigger[button];
		}

		/// <summary>
		/// マウスボタンが押されているかを取得。
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		const bool GetMouseButton(const MouseButton button) const
		{
			return m_mousePress[button];
		}

		/// <summary>
		/// マウスボタンが離された瞬間を取得。
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		const bool GetMouseButtonUp(const MouseButton button) const
		{
			return m_mouseRelease[button];
		}

		/// <summary>
		/// 何かしらのマウスボタンが押されているかを取得。
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
		/// マウスの座標を取得。
		/// </summary>
		/// <returns></returns>
		const Vector2& GetMousePosition() const
		{
			return m_mousePosition;
		}

		/// <summary>
		/// マウスの入力を取得。
		/// </summary>
		/// <returns>-1～1の間</returns>
		const Vector2& GetMouseAxis() const
		{
			return m_mouseAxis;
		}

		/// <summary>
		/// カーソルを固定にする。
		/// </summary>
		void LockCursor()
		{
			glfwSetInputMode(GraphicsEngine::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			m_cursorLock = true;
		}

		/// <summary>
		/// カーソルの固定を解除。
		/// </summary>
		void UnLockCursor()
		{
			glfwSetInputMode(GraphicsEngine::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_cursorLock = false;
		}

		/// <summary>
		/// カーソルの固定状態を取得。
		/// </summary>
		/// <returns></returns>
		const bool GetCursorLock() const
		{
			return m_cursorLock;
		}

	private:
		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="window"></param>
		void Init();
		/// <summary>
		/// キーの入力処理。
		/// </summary>
		void InputKey(GLFWwindow* window);
		/// <summary>
		/// マウスの入力処理。
		/// </summary>
		void InputMouse(GLFWwindow* window);

	private:
		static Input*	m_instance;							//インスタンス。
		Vector2			m_mousePosition;					//マウスの座標。
		Vector2			m_mouseAxis;						//マウスの入力。
		BitFlag			m_keyTriggerBit[(static_cast<int>(e_buttonNum) / INPUT_BIT_NUM_MAX) + 1];	//キーのトリガー判定。
		BitFlag			m_keyPressBit[(static_cast<int>(e_buttonNum) / INPUT_BIT_NUM_MAX) + 1];		//キーのプレス判定。
		BitFlag			m_keyReleaseBit[(static_cast<int>(e_buttonNum) / INPUT_BIT_NUM_MAX) + 1];	//キーのリリース判定。
		bool			m_mouseTrigger[e_mouseButtonNum];	//マウスのトリガー判定。
		bool			m_mousePress[e_mouseButtonNum];		//マウスのプレス判定。
		bool			m_mouseRelease[e_mouseButtonNum];	//マウスのリリース判定。
		bool			m_cursorLock = false;				//カーソルが固定かどうか。
	};
}

