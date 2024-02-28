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
			const int height,
			const int mipLevel,
			const GLenum format
		);

	private:
		GLuint m_fbo = 0;				//�t���[���o�b�t�@�[�B
		GLuint m_renderTexture = 0;		//�e�N�X�`���B
	};
}