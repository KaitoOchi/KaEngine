#include "KaEnginePreCompile.h"
#include "ShaderClass.h"

namespace nsKaEngine {

	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}

	void Shader::Init(
		const char* vertexFile,
		const char* fragmentFile,
		std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile
	) {
		//VertexShaderを作成。
		{
			std::string vertexCode = GetFileContents(vertexFile);

			for (auto& include : addIncludeFile)
			{
				vertexCode = AddIncludeShaderFile(vertexCode, include.c_str());
			}

			// Convert the shader source strings into character arrays
			char* vertexSource = const_cast<char*>(vertexCode.c_str());

			// Create Vertex Shader Object and get reference
			m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

			// Attach Vertex Shader source to the Vertex Shader Object
			glShaderSource(m_vertexShader, 1, &vertexSource, NULL);

			// Compile the Vertex Shader into machine code
			glCompileShader(m_vertexShader);
			ShaderCompileErrors(m_vertexShader, "VERTEX", vertexFile);
		}

		//FragmentShaderを作成。
		{
			std::string fragmentCode = GetFileContents(fragmentFile);

			for (auto& include : addIncludeFile)
			{
				fragmentCode = AddIncludeShaderFile(fragmentCode, include.c_str());
			}

			// Convert the shader source strings into character arrays
			char* fragmentSource = const_cast<char*>(fragmentCode.c_str());

			// Create Fragment Shader Object and get its reference
			m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			// Attach Fragment Shader source to the Fragment Shader Object
			glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);

			// Compile the Vertex Shader into machine code
			glCompileShader(m_fragmentShader);
			ShaderCompileErrors(m_fragmentShader, "FRAGMENT", fragmentFile);
		}

		// Creae Shader Program Object and get its reference
		m_id = glCreateProgram();
		// Attach the Vertex and Fragment Shaders to he Shader Program
		glAttachShader(m_id, m_vertexShader);
		glAttachShader(m_id, m_fragmentShader);
		// Wrap-up/Link all ther shaders together ino the Shader Program
		glLinkProgram(m_id);
		ShaderCompileErrors(m_id, "PROGRAM", nullptr);
	}

	std::string Shader::AddIncludeShaderFile(std::string mainShader, const char* includeFile)
	{
		std::string includeFileStr = includeFile;
		includeFileStr = "#include " + includeFileStr;

		// includeする位置にファイルの内容を挿入する
		size_t includePos = mainShader.find(includeFileStr);
		if (includePos != std::string::npos) {
			//インクルードファイルをロード。
			std::string fileName = "Assets/shader/";
			fileName = fileName + includeFile;
			std::string includedShaderCode = GetFileContents(const_cast<char*>(fileName.c_str()));
			//シェーダーに挿入する。
			mainShader.replace(includePos, strlen(const_cast<char*>(includeFileStr.c_str())), includedShaderCode);
		}
		return mainShader;
	}

	std::string Shader::GetFileContents(const char* filename)
	{
		std::ifstream in(filename, std::ios::binary);
		if (in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		throw(errno);
	}

	void Shader::ShaderCompileErrors(
		GLuint shader,
		const char* type,
		const char* filePath
	) {
		GLint hasCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {

			char infoLog[1024];

			if (type != "PROGRAM") {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				char errorMessage[1024];
				sprintf_s(errorMessage, "%s\n%s", filePath, infoLog);
				Ka_Assert(false, "ShaderCompileError", errorMessage);
			}
			else {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				Ka_Assert(false, "ShaderLinkingError", nullptr);
			}
		}
	}
}