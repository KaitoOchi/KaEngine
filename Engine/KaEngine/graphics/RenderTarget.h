#pragma once

namespace nsKaEngine {

	/// <summary>
	/// レンダーターゲット。
	/// </summary>
	class RenderTarget : Noncopyable
	{
	public:
		RenderTarget();
		~RenderTarget();

		/// <summary>
		/// レンダーターゲットの作成。
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="mipLevel"></param>
		/// <param name="format"></param>
		void Create(
			const int width,
			const int height,
			const int mipLevel,
			const GLenum format
		);

		/// <summary>
		/// レンダーテクスチャを取得。
		/// </summary>
		/// <returns></returns>
		Texture& GetRenderTargetTexture()
		{
			return m_renderTexture;
		}

		/// <summary>
		/// 画像の横幅を取得。
		/// </summary>
		/// <returns></returns>
		const int GetWidth() const
		{
			return m_width;
		}

		/// <summary>
		/// 画像の高さを取得。
		/// </summary>
		/// <returns></returns>
		const int GetHeight() const
		{
			return m_height;
		}

		/// <summary>
		/// IDを取得。
		/// </summary>
		/// <returns></returns>
		const GLuint GetID() const
		{
			return m_fbo;
		}

	private:
		Texture		m_renderTexture;		//レンダーテクスチャ。
		GLuint		m_fbo = 0;				//フレームバッファー。
		GLuint		m_depthBuffer = 0;		//深度バッファ。
		int			m_width = 0;			//横幅。
		int			m_height = 0;			//高さ。
	};
}
