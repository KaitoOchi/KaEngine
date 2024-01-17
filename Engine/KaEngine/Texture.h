#pragma once
#include <stb/stb_image.h>
#include "ShaderClass.h"

namespace nsKaEngine {

	class Texture
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
		/// �V�F�[�_�[�ɑ��M�B
		/// </summary>
		/// <param name="shader">�V�F�[�_�[</param>
		/// <param name="uniform">�ϐ���</param>
		/// <param name="unit">�X���b�g�ԍ�</param>
		void TexUnit(
			Shader* shader, 
			const char* uniform
		);

		/// <summary>
		/// �ڑ��B
		/// </summary>
		void Bind()
		{
			glActiveTexture(GL_TEXTURE0 + m_slot);
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
		GLuint m_slot = 0;		//�X���b�g�ԍ��B
	};
}