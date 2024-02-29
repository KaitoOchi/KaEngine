#pragma once
#include <stb/stb_image.h>
#include "ShaderClass.h"

namespace nsKaEngine {

	/// <summary>
	/// �e�N�X�`���[�B
	/// </summary>
	class Texture : Noncopyable
	{
	public:
		Texture();
		~Texture();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="image">�t�@�C���p�X�B</param>
		/// <param name="texType">�e�N�X�`���[�̎��</param>
		/// <param name="slot">�X���b�g�ԍ�</param>
		/// <param name="format">�t�H�[�}�b�g</param>
		/// <param name="pixelType">�s�N�Z���̎��</param>
		void Init(
			const char* image,
			const GLenum texType,
			const GLuint slot,
			const GLenum format,
			const GLenum pixelType
		);

		/// <summary>
		/// �����_�[�e�N�X�`�����쐬�B
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="mipLevel"></param>
		/// <param name="format"></param>
		void InitRenderTexture(
			const int width,
			const int height,
			const GLuint mipLevel,
			const GLenum format
		);

		/// <summary>
		/// �V�F�[�_�[�ɑ��M�B
		/// </summary>
		/// <param name="shader">�V�F�[�_�[</param>
		/// <param name="uniform">�ϐ���</param>
		/// <param name="slot">�X���b�g�ԍ�</param>
		void TexUnit(
			const Shader* shader, 
			const char* uniform,
			const GLuint slot
		);

		/// <summary>
		/// �e�N�X�`���[ID���擾�B
		/// </summary>
		/// <returns></returns>
		const GLuint GetTextureID() const
		{
			return m_id;
		}

		/// <summary>
		/// �ڑ��B
		/// </summary>
		void Bind(const GLuint slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(m_target, m_id);
		}

		/// <summary>
		/// �����B
		/// </summary>
		void UnBind()
		{
			glBindTexture(m_target, 0);
		}

		/// <summary>
		/// �폜�B
		/// </summary>
		void Delete()
		{
			glDeleteTextures(1, &m_id);
		}

	private:
		GLuint m_id = 0;		//�e�N�X�`���[ID�B
		GLenum m_target = 0;	//�e�N�X�`���[�̎�ށB
	};
}