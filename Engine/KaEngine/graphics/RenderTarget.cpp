#include "KaEnginePreCompile.h"
#include "RenderTarget.h"

namespace nsKaEngine {

	RenderTarget::RenderTarget()
	{

	}

	RenderTarget::~RenderTarget()
	{
		glDeleteFramebuffers(1, &m_fbo);
		glDeleteRenderbuffers(1, &m_depthBuffer);
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
		if (m_fbo == 0) {
			glGenFramebuffers(1, &m_fbo);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		//�����_�[�e�N�X�`���̍쐬�B
		m_renderTexture.InitRenderTexture(
			m_width,
			m_height,
			mipLevel,
			format
		);

		//�f�v�X�o�b�t�@�̍쐬�B
		if (m_depthBuffer == 0) {
			glGenRenderbuffers(1, &m_depthBuffer);
		}
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Ka_Assert(false, "codeError", "RenderTarget�̍쐬�Ɏ��s���܂����B");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
