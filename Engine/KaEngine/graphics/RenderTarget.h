#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �����_�[�^�[�Q�b�g�B
	/// </summary>
	class RenderTarget : Noncopyable
	{
	public:
		RenderTarget();
		~RenderTarget();


		void Create(
			const int width,
			const int height
		);

	private:
		GLuint m_frameBuffer = 0;
		GLuint m_renderTexture = 0;
	};
}