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

		//フレームバッファの作成。
		if (m_fbo == 0) {
			glGenFramebuffers(1, &m_fbo);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		//レンダーテクスチャの作成。
		m_renderTexture.InitRenderTexture(
			m_width,
			m_height,
			mipLevel,
			format
		);

		//デプスバッファの作成。
		if (m_depthBuffer == 0) {
			glGenRenderbuffers(1, &m_depthBuffer);
		}
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Ka_Assert(false, "codeError", "RenderTargetの作成に失敗しました。");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
