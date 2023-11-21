#pragma once

namespace nsKaEngine{

	/// <summary>
	/// キーコード。
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
	/// マウスボタン。
	/// </summary>
	enum MouseButton
	{
		enMouseButtonLeft,
		enMouseButtonRight,
		enMouseButtonMiddle,
		enMouseButtonNum,
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
		static void CreateInstance(GLFWwindow* window)
		{
			if (m_instance != nullptr) {
				std::abort();
			}
			m_instance = new Input;
			m_instance->Init(window);
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
		/// 初期化処理。
		/// </summary>
		/// <param name="window"></param>
		void Init(GLFWwindow* window);

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
			return m_keyTrigger[code];
		}

		/// <summary>
		/// ボタンが押されているかを取得。
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKey(const KeyCode code) const
		{
			return m_keyPress[code];
		}

		/// <summary>
		/// ボタンが離された瞬間を取得。
		/// </summary>
		/// <param name="code"></param>
		/// <returns></returns>
		const bool GetKeyUp(const KeyCode code) const
		{
			return m_keyRelease[code];
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
		/// マウスの座標を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetMousePosition() const
		{
			return m_mousePosition;
		}

		/// <summary>
		/// マウスの入力を取得。
		/// </summary>
		/// <returns>-1～1の間</returns>
		const Vector3& GetMouseAxis() const
		{
			return m_mouseAxis;
		}

		/// <summary>
		/// カーソルを固定にする。
		/// </summary>
		void LockCursor()
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			m_cursorLock = true;
		}

		/// <summary>
		/// カーソルの固定を解除。
		/// </summary>
		void UnLockCursor()
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
		/// キーの入力処理。
		/// </summary>
		void InputKey();
		/// <summary>
		/// マウスの入力処理。
		/// </summary>
		void InputMouse();

	private:
		static Input*	m_instance;							//インスタンス。
		GLFWwindow*		m_window = nullptr;					//ウィンドウ。
		Vector3			m_mousePosition;					//マウスの座標。
		Vector3			m_mouseAxis;						//マウスの入力。
		bool			m_keyTrigger[enButtonNum];			//キーのトリガー判定。
		bool			m_keyPress[enButtonNum];			//キーのプレス判定。
		bool			m_keyRelease[enButtonNum];			//キーのリリース判定。
		bool			m_mouseTrigger[enMouseButtonNum];	//マウスのトリガー判定。
		bool			m_mousePress[enMouseButtonNum];		//マウスのプレス判定。
		bool			m_mouseRelease[enMouseButtonNum];	//マウスのリリース判定。
		bool			m_cursorLock = false;				//カーソルが固定かどうか。
	};
}

