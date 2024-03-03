#pragma once
#include <fstream>

namespace nsKaEngine {

	namespace
	{
		const int ADD_INCLUDE_FILE_MAX = 8;		//追加インクルードファイルの最大数。
	}

	/// <summary>
	/// シェーダークラス。
	/// </summary>
	class Shader : Noncopyable
	{
	public:
		Shader();
		~Shader();

		/// <summary>
		/// 初期化処理。
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
		/// シェーダーIDを取得。
		/// </summary>
		/// <returns></returns>
		const GLuint GetShaderID() const
		{
			return m_id;
		}

		/// <summary>
		/// 有効化。
		/// </summary>
		void Activate()
		{
			glUseProgram(m_id);
		}

		/// <summary>
		/// 削除。
		/// </summary>
		void Delete()
		{
			glDeleteProgram(m_id);
			glDeleteShader(m_vertexShader);
			glDeleteShader(m_fragmentShader);
		}

	private:
		/// <summary>
		/// ファイルからテキストを出力。
		/// </summary>
		/// <param name="fileName"></param>
		/// <returns></returns>
		std::string GetFileContents(const char* fileName);
		/// <summary>
		/// シェーダーにインクルードファイルを挿入する。
		/// </summary>
		/// <param name="mainShader">元になるシェーダー</param>
		/// <param name="includeFile">インクルードしたいファイル</param>
		/// <returns></returns>
		std::string AddIncludeShaderFile(
			std::string mainShader,
			const char* includeFile
		);
		/// <summary>
		/// コンパイルエラーを出力。
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="type"></param>
		void ShaderCompileErrors(
			GLuint shader,
			const char* type,
			const char* filePath
		);

	private:
		GLuint m_id = 0;				//シェーダープログラム。
		GLuint m_vertexShader = 0;		//頂点シェーダー。
		GLuint m_fragmentShader = 0;	//フラグメントシェーダー。
	};
}