#pragma once

namespace nsKaEngine {

	/// <summary>
	/// グラフィックスエンジン。
	/// </summary>
	class GraphicsEngine : Noncopyable
	{
	public:
		GraphicsEngine() {}
		~GraphicsEngine() {}

		/// <summary>
		/// インスタンスの作成。
		/// </summary>
		static void CreateInstance(
			GLFWwindow* window,
			Config* deviceInfo
		) {
			Ka_Assert(m_instance == nullptr, "codeError", "GaphicsEngineクラスのインスタンスは一つしか作れません。");
			m_instance = new GraphicsEngine;
			m_instance->Init(window, deviceInfo);
		}

		/// <summary>
		/// インスタンスの取得。
		/// </summary>
		/// <returns></returns>
		static GraphicsEngine* GetInstance()
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
		/// ウィンドウを取得。
		/// </summary>
		/// <returns></returns>
		GLFWwindow* GetWindow() const
		{
			return m_window;
		}

		/// <summary>
		/// ウィンドウサイズを取得。
		/// </summary>
		/// <returns></returns>
		const Vector2Int& GetWindowSize() const
		{
			return m_frameBufferSize;
		}

		/// <summary>
		/// フルスクリーン状態の切り替え。
		/// </summary>
		void ToggleFullScreen()
		{
			Vector2 framebufferSize;
			framebufferSize = m_frameBufferSize;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			if (!m_isFullScreen) {
				framebufferSize.Scale(1.2f);
				glfwSetWindowMonitor(m_window, monitor, 0, 0, static_cast<int>(framebufferSize.x), static_cast<int>(framebufferSize.y), GLFW_DONT_CARE);
			}
			else {
				framebufferSize.Div(1.2f);
				glfwSetWindowMonitor(m_window, NULL, 0, 35, static_cast<int>(framebufferSize.x), static_cast<int>(framebufferSize.y), GLFW_DONT_CARE);
			}
			m_frameBufferSize = framebufferSize;
			m_renderContext.SetViewportAndScissor(m_frameBufferSize.x, m_frameBufferSize.y);
			m_isFullScreen = !m_isFullScreen;
		}

		/// <summary>
		/// 実行処理。
		/// </summary>
		void Execute();

		/// <summary>
		/// レンダリングコンテキストを取得。
		/// </summary>
		/// <returns></returns>
		RenderContext& GetRenderContext()
		{
			return m_renderContext;
		}

		/// <summary>
		/// メインレンダーターゲットを取得。
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetRenderTarget()
		{
			return m_mainRenderTarget;
		}

		void Test();


	private:
		/// <summary>
		/// 初期化処理。
		/// </summary>
		void Init(
			GLFWwindow* window,
			Config* deviceInfo
		);

	private:
		static GraphicsEngine*	m_instance;				//インスタンス。
		GLFWwindow*				m_window = nullptr;		//ウィンドウ。
		RenderContext			m_renderContext;		//レンダリングコンテキスト。

		RenderTarget			m_mainRenderTarget;		//レンダーターゲット。
		Sprite					m_mainSprite;			//メイン画像。
		Vector2Int				m_frameBufferSize;		//ウィンドウサイズ。
		bool					m_isFullScreen = false;	//フルスクリーンかどうか。
	};
}
