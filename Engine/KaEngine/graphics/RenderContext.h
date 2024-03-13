#pragma once

namespace nsKaEngine {

	/// <summary>
	/// レンダリングコンテキスト。
	/// </summary>
	class RenderContext : Noncopyable
	{
	public:

		/// <summary>
		/// レンダーターゲットのクリア。
		/// </summary>
		void ClearRenderTarget()
		{
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		/// <summary>
		/// レンダーターゲットの接続。
		/// </summary>
		/// <param name="rt"></param>
		void BindRenderTarget(RenderTarget& rt)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, rt.GetID());
		}

		/// <summary>
		/// レンダーターゲットとビューポートの設定。
		/// </summary>
		/// <param name="rt"></param>
		void BindRenderTargetAndViewport(RenderTarget& rt)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, rt.GetID());
			SetViewportAndScissor(rt.GetWidth(), rt.GetHeight());
		}

		/// <summary>
		/// レンダーターゲットの接続を解除。
		/// </summary>
		void UnBindRenderTarget()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		/// <summary>
		/// ビューポートとシザリング矩形を設定。
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetViewportAndScissor(const int width, const int height)
		{
			SetViewport(0, 0, width, height);
			SetScissor(0, 0, width, height);
		}

		/// <summary>
		/// ビューポートを設定。
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetViewport(
			const int x,
			const int y,
			const int width,
			const int height
		) {
			glViewport(x, y, width, height);
		}

		/// <summary>
		/// シザリング矩形を設定。
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetScissor(
			const int x,
			const int y,
			const int width,
			const int height
		) {
			glScissor(x, y, width, height);
		}

	private:
	};
}
