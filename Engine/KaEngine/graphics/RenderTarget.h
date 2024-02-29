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

		/// <summary>
		/// �����_�[�^�[�Q�b�g�̍쐬�B
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
		/// �����_�[�e�N�X�`�����擾�B
		/// </summary>
		/// <returns></returns>
		Texture& GetRenderTargetTexture()
		{
			return m_renderTexture;
		}

		/// <summary>
		/// �摜�̉������擾�B
		/// </summary>
		/// <returns></returns>
		const int GetWidth() const
		{
			return m_width;
		}

		/// <summary>
		/// �摜�̍������擾�B
		/// </summary>
		/// <returns></returns>
		const int GetHeight() const
		{
			return m_height;
		}

	public:
		/// <summary>
		/// �ڑ��B
		/// </summary>
		void Bind();
		/// <summary>
		/// �����B
		/// </summary>
		void UnBind();

	private:
		Texture m_renderTexture;		//�����_�[�e�N�X�`���B
		GLuint m_fbo = 0;				//�t���[���o�b�t�@�[�B
		int m_width = 0;				//�����B
		int m_height = 0;				//�����B
	};
}
