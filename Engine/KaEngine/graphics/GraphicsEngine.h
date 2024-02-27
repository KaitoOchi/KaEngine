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
		static void CreateInstance(GLFWwindow* window)
		{
			Ka_Assert(m_instance == nullptr, "codeError", "GaphicsEngineクラスのインスタンスは一つしか作れません。");
			m_instance = new GraphicsEngine;
			m_instance->Init(window);
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
		/// ウィンドウの固定を有効化。
		/// </summary>
		void ActiveFixedWindow()
		{
			int w = static_cast<int>(m_frameBufferSize.x);
			int h = static_cast<int>(m_frameBufferSize.y);
			glfwSetWindowSizeLimits(m_window, w, h, w, h);
		}

		/// <summary>
		/// ウィンドウの固定を無効化。
		/// </summary>
		void DeactiveFixedWindow()
		{
			glfwSetWindowSizeLimits(m_window, 0, 0, static_cast<int>(m_frameBufferSize.x), static_cast<int>(m_frameBufferSize.y));
		}

		/// <summary>
		/// ウィンドウサイズを取得。
		/// </summary>
		/// <returns></returns>
		const Vector2& GetWindowSize() const
		{
			return m_frameBufferSize;
		}

		/// <summary>
		/// 実行処理。
		/// </summary>
		void Execute();


	private:
		/// <summary>
		/// 初期化処理。
		/// </summary>
		void Init(GLFWwindow* window);

	private:
		static GraphicsEngine*	m_instance;				//インスタンス。
		GLFWwindow*				m_window = nullptr;		//ウィンドウ。
		Vector2					m_frameBufferSize;		//ウィンドウサイズ。

	};
}