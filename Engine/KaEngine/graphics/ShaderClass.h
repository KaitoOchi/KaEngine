#pragma once
#include <fstream>

namespace nsKaEngine {

	namespace
	{
		const int ADD_INCLUDE_FILE_MAX = 8;		//�ǉ��C���N���[�h�t�@�C���̍ő吔�B
	}

	/// <summary>
	/// �V�F�[�_�[�N���X�B
	/// </summary>
	class Shader : Noncopyable
	{
	public:
		Shader();
		~Shader();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="vertexFile"></param>
		/// <param name="fragmentFile"></param>
		/// <param name="addIncludeFile"></param>
		void Init(
			const char* vertexFile,
			const char* fragmentFile,
			std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile
		);

		/// <summary>
		/// �V�F�[�_�[ID���擾�B
		/// </summary>
		/// <returns></returns>
		const GLuint GetShaderID() const
		{
			return m_id;
		}

		/// <summary>
		/// �L�����B
		/// </summary>
		void Activate()
		{
			glUseProgram(m_id);
		}

		/// <summary>
		/// �폜�B
		/// </summary>
		void Delete()
		{
			glDeleteProgram(m_id);
			glDeleteShader(m_vertexShader);
			glDeleteShader(m_fragmentShader);
		}

	private:
		/// <summary>
		/// �t�@�C������e�L�X�g���o�́B
		/// </summary>
		/// <param name="fileName"></param>
		/// <returns></returns>
		std::string GetFileContents(const char* fileName);
		/// <summary>
		/// �V�F�[�_�[�ɃC���N���[�h�t�@�C����}������B
		/// </summary>
		/// <param name="mainShader">���ɂȂ�V�F�[�_�[</param>
		/// <param name="includeFile">�C���N���[�h�������t�@�C��</param>
		/// <returns></returns>
		std::string AddIncludeShaderFile(
			std::string mainShader,
			const char* includeFile
		);
		/// <summary>
		/// �R���p�C���G���[���o�́B
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="type"></param>
		void ShaderCompileErrors(
			GLuint shader,
			const char* type,
			const char* filePath
		);

	private:
		GLuint m_id = 0;				//�V�F�[�_�[�v���O�����B
		GLuint m_vertexShader = 0;		//���_�V�F�[�_�[�B
		GLuint m_fragmentShader = 0;	//�t���O�����g�V�F�[�_�[�B
	};
}