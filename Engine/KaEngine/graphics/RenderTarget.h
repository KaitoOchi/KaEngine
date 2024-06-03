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
			const GLenum format,
			const Vector4 clearColor = Vector4::Gray
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

		/// <summary>
		/// �N���A�J���[���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector4& GetClearColor() const
		{
			return m_clearColor;
		}

		/// <summary>
		/// ID���擾�B
		/// </summary>
		/// <returns></returns>
		const GLuint GetID() const
		{
			return m_fbo;
		}

	private:
		Texture		m_renderTexture;				//�����_�[�e�N�X�`���B
		GLuint		m_fbo = 0;						//�t���[���o�b�t�@�[�B
		GLuint		m_depthBuffer = 0;				//�[�x�o�b�t�@�B
		Vector4		m_clearColor = Vector4::Gray;	//�N���A�J���[�B
		int			m_width = 0;					//�����B
		int			m_height = 0;					//�����B
	};
}
