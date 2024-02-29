#include "KaEnginePreCompile.h"
#include "RenderTarget.h"

namespace nsKaEngine {

	RenderTarget::RenderTarget()
	{

	}

	RenderTarget::~RenderTarget()
	{

	}

	void RenderTarget::Create(
		const int width,
		const int height,
		const int mipLevel,
		const GLenum format
	){
		m_width = width;
		m_height = height;

		//�t���[���o�b�t�@�̍쐬�B
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		//�����_�[�e�N�X�`���̍쐬�B
		m_renderTexture.InitRenderTexture(
			m_width,
			m_height,
			mipLevel,
			format
		);

		//�f�v�X�o�b�t�@�̍쐬�B
		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Ka_Assert(false, "codeError", "RenderTarget�̍쐬�Ɏ��s���܂����B");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderTarget::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderTarget::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
