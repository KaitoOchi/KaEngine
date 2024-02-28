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
		//フレームバッファの作成。
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		//レンダーテクスチャの作成。
		glGenTextures(1, &m_renderTexture);
		glBindTexture(GL_TEXTURE_2D, m_renderTexture);
		glTexImage2D(GL_TEXTURE_2D, mipLevel, format, width, height, 0, format, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderTexture, 0);

		//デプスバッファの作成。
		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

		// Set the list of draw buffers.
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Ka_Assert(false, "codeError", "RenderTargetの作成に失敗しました。");
		}
	}
}