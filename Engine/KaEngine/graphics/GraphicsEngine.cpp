#include "KaEnginePreCompile.h"
#include "GraphicsEngine.h"

namespace nsKaEngine {

	GraphicsEngine* GraphicsEngine::m_instance = nullptr;

	void GraphicsEngine::Init(
		GLFWwindow* window,
		Config* deviceInfo
	) {
		m_window = window;

		//ウィンドウサイズの設定。
		m_frameBufferSize.Set(deviceInfo->windowWidth, deviceInfo->windowHeight);
		m_renderContext.SetViewportAndScissor(deviceInfo->windowWidth, deviceInfo->windowHeight);

		if (deviceInfo->fullscreen == true) {
			ToggleFullScreen();
		}

		//デプステストの有効化。
		glEnable(GL_DEPTH_TEST);

		//シザリングテストの有効化。
		glEnable(GL_SCISSOR_TEST);

		//背面カリングを有効にする。
		//glEnable(GL_CULL_FACE);

		//MSAAの有効化。
		glEnable(GL_MULTISAMPLE);

		//半透明描画を適用。
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//メインレンダーターゲットの作成。
		m_mainRenderTarget.Create(
			deviceInfo->windowWidth,
			deviceInfo->windowHeight,
			0,
			GL_RGB
		);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

		//メインレンダーターゲット用スプライトの設定。
		SpriteInitData spriteInitData;
		spriteInitData.textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		spriteInitData.vertexFilePath = "Assets/shader/sprite.vert";
		spriteInitData.fragmentFilePath = "Assets/shader/sprite.frag";
		spriteInitData.width = 1920;
		spriteInitData.height = 1080;
		m_mainSprite.Init(spriteInitData);
	}

	void GraphicsEngine::Execute()
	{
		//フレームバッファをクリア。
		m_renderContext.UnBindRenderTarget();
		m_renderContext.ClearRenderTarget();

		VIEWPORT viewport = m_renderContext.GetViewport();

		//Fキーでフルスクリーンモード。
		if (Input::GetInstance()->GetKeyDown(e_buttonF)) {
			ToggleFullScreen();
			m_mainRenderTarget.Create(
				viewport.width,
				viewport.height,
				0,
				GL_RGB
			);
		}
	}

	void GraphicsEngine::Test()
	{
		m_mainSprite.Draw(m_renderContext);
	}
}
