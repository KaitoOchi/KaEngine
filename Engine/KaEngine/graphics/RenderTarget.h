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


		void Create(
			const int width,
			const int height,
			const int mipLevel,
			const GLenum format
		);

	private:
		GLuint m_fbo = 0;				//フレームバッファー。
		GLuint m_renderTexture = 0;		//テクスチャ。
	};
}