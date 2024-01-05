#include "KaEnginePreCompile.h"
#include "ShaderClass.h"

namespace nsKaEngine {

	// Reads a text file and outputs a string with everything in the text file
	std::string get_file_contents(const char* filename)
	{
		std::ifstream in(filename, std::ios::binary);
		if (in)
		{
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

	Shader::Shader()
	{

	}

	Shader::~Shader()
	{
		// Delete the now useless ertext and Fragment Shader Objects
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);
	}

	void Shader::Init(const char* vertexFile, const char* fragmentFile)
	{
		//VertexShaderを作成。
		GLuint* vertexShaderPtr = KaEngine::GetInstance()->GetShaderBank(vertexFile);
		if (vertexShaderPtr == nullptr) {
			// Read vertexFile and fragmentFile and store the strings
			std::string vertexCode = get_file_contents(vertexFile);
			vertexCode = AddIncludeShaderFile(vertexCode, "PBRLighting.h");
			vertexCode = AddIncludeShaderFile(vertexCode, "PBRLighting_struct.h");
			// Convert the shader source strings into character arrays
			char* vertexSource = const_cast<char*>(vertexCode.c_str());
			// Create Vertex Shader Object and get reference
			m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
			// Attach Vertex Shader source to the Vertex Shader Object
			glShaderSource(m_vertexShader, 1, &vertexSource, NULL);
			// Compile the Vertex Shader into machine code
			glCompileShader(m_vertexShader);
			compileErrors(m_vertexShader, "VERTEX");

			vertexShaderPtr = &m_vertexShader;
			KaEngine::GetInstance()->RegistShaderBank(vertexFile, vertexShaderPtr);
		}
		else {
			m_vertexShader = *vertexShaderPtr;
		}

		//FragmentShaderを作成。
		GLuint* fragmentShaderPtr = KaEngine::GetInstance()->GetShaderBank(fragmentFile);
		if (fragmentShaderPtr == nullptr) {
			// Read vertexFile and fragmentFile and store the strings
			std::string fragmentCode = get_file_contents(fragmentFile);
			fragmentCode = AddIncludeShaderFile(fragmentCode, "PBRLighting.h");
			fragmentCode = AddIncludeShaderFile(fragmentCode, "PBRLighting_struct.h");
			// Convert the shader source strings into character arrays
			char* fragmentSource = const_cast<char*>(fragmentCode.c_str());
			// Create Fragment Shader Object and get its reference
			m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			// Attach Fragment Shader source to the Fragment Shader Object
			glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);
			// Compile the Vertex Shader into machine code
			glCompileShader(m_fragmentShader);
			compileErrors(m_fragmentShader, "FRAGMENT");

			fragmentShaderPtr = &m_fragmentShader;
			KaEngine::GetInstance()->RegistShaderBank(fragmentFile, fragmentShaderPtr);
		}
		else {
			m_fragmentShader = *fragmentShaderPtr;
		}

		// Creae Shader Program Object and get its reference
		ID = glCreateProgram();
		// Attach the Vertex and Fragment Shaders to he Shader Program
		glAttachShader(ID, m_vertexShader);
		glAttachShader(ID, m_fragmentShader);
		// Wrap-up/Link all ther shaders together ino the Shader Program
		glLinkProgram(ID);
		compileErrors(ID, "PROGRAM");
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
			std::string includedShaderCode = get_file_contents(const_cast<char*>(fileName.c_str()));
			//シェーダーに挿入する。
			mainShader.replace(includePos, strlen(const_cast<char*>(includeFileStr.c_str())), includedShaderCode);
		}

		return mainShader;
	}

	void Shader::Activate()
	{
		glUseProgram(ID);
	}

	void Shader::Delete()
	{
		glDeleteProgram(ID);
	}

	void Shader::compileErrors(unsigned int shader, const char* type)
	{
		GLint hasCompiled;
		char infoLog[1024];

		if (type != "PROGRAM") {

			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILAION_ERROR for:" << type << "\n" << std::endl;
			}
		}
		else {

			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
			}
		}
	}
}