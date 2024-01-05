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
		Material() {}
		~Material(){}

		void Init(
			const char* albedoFilePath,
			const char* normalFilePath,
			const char* metallicSmoothFilePath,
			const char* vsFilePath,
			const char* fsFilePath
		);

	private:
		Texture* m_albedoMap = nullptr;
		Texture* m_normalMap = nullptr;
		Texture* m_metallicSmoothMap = nullptr;
		Shader* m_vertexShader = nullptr;
		Shader* m_fragmentShader = nullptr;
	};
}

