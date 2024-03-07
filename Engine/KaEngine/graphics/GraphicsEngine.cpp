#include "KaEnginePreCompile.h"
#include "GraphicsEngine.h"

namespace nsKaEngine {

	GraphicsEngine* GraphicsEngine::m_instance = nullptr;

	void GraphicsEngine::Init(
		GLFWwindow* window,
		DeviceInfo* deviceInfo
	) {
		m_window = window;

		m_frameBufferSize.Set(deviceInfo->windowWidth, deviceInfo->windowHeight);

		if (deviceInfo->fullscreen == true) {
			ToggleFullScreen();
		}

		//�f�v�X�e�X�g�̗L�����B
		glEnable(GL_DEPTH_TEST);

		//�w�ʃJ�����O��L���ɂ���B
		//glEnable(GL_CULL_FACE);

		//MSAA�̗L�����B
		glEnable(GL_MULTISAMPLE);

		//�������`���K�p�B
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		spriteInitData.width = 1920;
		spriteInitData.height = 1080;
		m_mainSprite.Init(spriteInitData);
	}

	void GraphicsEngine::Execute()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Clear the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//�E�B���h�E�T�C�Y���擾�B
		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		m_frameBufferSize.Set(static_cast<float>(width), static_cast<float>(height));
		glViewport(0, 0, width, height);

		if (Input::GetInstance()->GetKeyDown(e_buttonF)) {
			ToggleFullScreen();
		}
	}

	void GraphicsEngine::Test()
	{
		m_mainSprite.Draw();
	}
}
