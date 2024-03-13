#include "KaEnginePreCompile.h"
#include "GraphicsEngine.h"

namespace nsKaEngine {

	GraphicsEngine* GraphicsEngine::m_instance = nullptr;

	void GraphicsEngine::Init(
		GLFWwindow* window,
		Config* deviceInfo
	) {
		m_window = window;

		//�E�B���h�E�T�C�Y�̐ݒ�B
		m_frameBufferSize.Set(deviceInfo->windowWidth, deviceInfo->windowHeight);
		m_renderContext.SetViewportAndScissor(m_frameBufferSize.x, m_frameBufferSize.y);

		if (deviceInfo->fullscreen == true) {
			ToggleFullScreen();
		}

		//�f�v�X�e�X�g�̗L�����B
		glEnable(GL_DEPTH_TEST);

		//�V�U�����O�e�X�g�̗L�����B
		glEnable(GL_SCISSOR_TEST);

		//�w�ʃJ�����O��L���ɂ���B
		//glEnable(GL_CULL_FACE);

		//MSAA�̗L�����B
		glEnable(GL_MULTISAMPLE);

		//�������`���K�p�B
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//���C�������_�[�^�[�Q�b�g�̍쐬�B
		m_mainRenderTarget.Create(
			m_frameBufferSize.x,
			m_frameBufferSize.y,
			0,
			GL_RGB
		);

		//���C�������_�[�^�[�Q�b�g�p�X�v���C�g�̐ݒ�B
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
		//�t���[���o�b�t�@���N���A�B
		m_renderContext.UnBindRenderTarget();
		m_renderContext.ClearRenderTarget();

		//F�L�[�Ńt���X�N���[�����[�h�B
		if (Input::GetInstance()->GetKeyDown(e_buttonF)) {
			ToggleFullScreen();
			m_mainRenderTarget.Create(
				m_frameBufferSize.x,
				m_frameBufferSize.y,
				0,
				GL_RGB
			);
		}
	}

	void GraphicsEngine::Test()
	{
		m_mainSprite.Draw();
	}
}
