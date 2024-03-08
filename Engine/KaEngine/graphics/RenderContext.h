#pragma once

namespace nsKaEngine {

	class RenderContext : Noncopyable
	{
	public:

		void ClearRenderTarget()
		{
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void BindRenderTarget(RenderTarget& rt)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, rt.GetID());
			//SetViewport(rt.GetWidth(), rt.GetHeight());
			//SetScissor(rt.GetWidth(), rt.GetHeight());
		}

		void UnBindRenderTarget()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void SetViewport(const int width, const int height)
		{
			glViewport(0, 0, width, height);
		}

		void SetScissor(const int width, const int height)
		{
			glScissor(0, 0, width, height);
		}

	private:
	};
}