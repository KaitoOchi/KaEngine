#include "KaEnginePreCompile.h"
#include "GraphicsEngine.h"

namespace nsKaEngine {

	GraphicsEngine* GraphicsEngine::m_instance = nullptr;

	void GraphicsEngine::Init(GLFWwindow* window)
	{
		m_window = window;

		m_frameBufferSize.Set(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);

		//デプステストの有効化。
		glEnable(GL_DEPTH_TEST);

		//背面カリングを有効にする。
		//glEnable(GL_CULL_FACE);

		//MSAAの有効化。
		//glEnable(GL_MULTISAMPLE);

		//半透明描画を適用。
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glfwMaximizeWindow(m_window);

		m_mainRenderTarget.Create(
			static_cast<int>(m_frameBufferSize.x),
			static_cast<int>(m_frameBufferSize.y),
			0,
			GL_RGB
		);

		SpriteInitData spriteInitData;
		spriteInitData.textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		spriteInitData.vertexFilePath = "Assets/shader/sprite.vert";
		spriteInitData.fragmentFilePath = "Assets/shader/sprite.frag";
		spriteInitData.width = static_cast<int>(m_frameBufferSize.x);
		spriteInitData.height = static_cast<int>(m_frameBufferSize.y);
		m_mainSprite.Init(spriteInitData);


		ActiveFixedWindow();
	}

	void GraphicsEngine::Execute()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Clear the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//ウィンドウサイズを取得。
		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		m_frameBufferSize.Set(static_cast<float>(width), static_cast<float>(height));
		glViewport(0, 0, width, height);
	}

	void GraphicsEngine::Test()
	{
		m_mainSprite.Draw();
	}
}