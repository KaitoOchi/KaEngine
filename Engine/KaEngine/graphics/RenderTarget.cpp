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
		m_renderTexture.Delete();
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
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		//レンダーテクスチャの作成。
		m_renderTexture.InitRenderTexture(
			m_width,
			m_height,
			mipLevel,
			format
		);

		//デプスバッファの作成。
		glGenRenderbuffers(1, &m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Ka_Assert(false, "codeError", "RenderTargetの作成に失敗しました。");
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
