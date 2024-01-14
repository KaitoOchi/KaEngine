#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

namespace nsKaEngine {

	class Shader
	{
	public:
		// Reference ID of the Shader Program
		GLuint ID = 0;
		// build the Shader Program from 2 different shaders
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
			std::array<std::string, 8> addIncludeFile
		);

		/// <summary>
		/// �V�F�[�_�[�ɃC���N���[�h�t�@�C����}������B
		/// </summary>
		/// <param name="mainShader">���ɂȂ�V�F�[�_�[</param>
		/// <param name="includeFile">�C���N���[�h�������t�@�C��</param>
		/// <returns></returns>
		std::string AddIncludeShaderFile(std::string mainShader, const char* includeFile);

		void Activate();
		void Delete();

	private:
		/// <summary>
		/// �t�@�C������e�L�X�g���o�́B
		/// </summary>
		/// <param name="fileName"></param>
		/// <returns></returns>
		std::string GetFileContents(const char* fileName);

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
		GLuint m_vertexShader = 0;
		GLuint m_fragmentShader = 0;
	};
}