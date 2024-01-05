#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

namespace nsKaEngine {

	std::string get_file_contents(const char* fileName);

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
		void Init(const char* vertexFile, const char* fragmentFile);

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
		void compileErrors(unsigned int shader, const char* type);

		GLuint m_vertexShader = 0;
		GLuint m_fragmentShader = 0;
	};
}