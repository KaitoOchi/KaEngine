#pragma once
class Texture;
class Shader;

namespace nsKaEngine {

	/// <summary>
	/// マテリアルクラス。
	/// </summary>
	class Material : Noncopyable
	{
	public:
		Material();
		~Material();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="albedoFilePath"></param>
		/// <param name="normalFilePath"></param>
		/// <param name="metallicSmoothFilePath"></param>
		/// <param name="vsFilePath"></param>
		/// <param name="fsFilePath"></param>
		/// <param name="addIncludeFile"></param>
		void Init(
			std::string albedoFilePath,
			std::string normalFilePath,
			std::string metallicSmoothFilePath,
			std::string vsFilePath,
			std::string fsFilePath,
			std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile
		);

		
		const GLuint GetShaderID() const
		{
			return m_shaderProgram.GetShaderID();
		}

		void ShaderActivate()
		{
			m_shaderProgram.Activate();
		}

	private:
		Texture*	m_albedoMap = nullptr;
		Texture*	m_normalMap = nullptr;
		Texture*	m_metallicSmoothMap = nullptr;
		Shader		m_shaderProgram;
	};
}

