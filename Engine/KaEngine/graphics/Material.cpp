#include "KaEnginePreCompile.h"
#include "Material.h"
#include "Texture.h"

namespace nsKaEngine {

	namespace
	{
		const int	MAX_TEXTURE_NUM = 3;
		const char* TEXTURE_NAME[MAX_TEXTURE_NUM] = { "g_albedoMap",
							"g_normalMap",
							"g_metallicSmoothMap"
		};
	}

	Material::Material()
	{
		m_textures.reserve(MAX_TEXTURE_NUM);
	}

	Material::~Material()
	{
		m_shaderProgram->Delete();
		m_textures.clear();
		m_textures.shrink_to_fit();
	}

	void Material::Init(
		std::string albedoFilePath,
		std::string normalFilePath,
		std::string metallicSmoothFilePath,
		std::string vsFilePath,
		std::string fsFilePath,
		std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile
	) {
		//シェーダーの設定。
		auto shader = KaEngine::GetInstance()->GetShaderBank(vsFilePath.c_str());
		if (shader == nullptr) {
			shader = new Shader;
			shader->Init(vsFilePath.c_str(), fsFilePath.c_str(), addIncludeFile);
			KaEngine::GetInstance()->RegistShaderBank(vsFilePath.c_str(), shader);
		}
		m_shaderProgram = shader;
		m_shaderProgram->Activate();

		//アルベドマップ。
		auto albedoMap = KaEngine::GetInstance()->GetTextureBank(albedoFilePath.c_str());
		if (albedoMap == nullptr) {
			albedoMap = new Texture;
			albedoMap->Init(albedoFilePath.c_str(), GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
			KaEngine::GetInstance()->RegistTextureBank(albedoFilePath.c_str(), albedoMap);
		}
		albedoMap->TexUnit(m_shaderProgram, TEXTURE_NAME[0], 0);
		m_textures.emplace_back(albedoMap);

		//法線マップ。
		auto normalMap = KaEngine::GetInstance()->GetTextureBank(normalFilePath.c_str());
		if (normalMap == nullptr) {
			normalMap = new Texture;
			normalMap->Init(normalFilePath.c_str(), GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);
			KaEngine::GetInstance()->RegistTextureBank(normalFilePath.c_str(), normalMap);
		}
		normalMap->TexUnit(m_shaderProgram, TEXTURE_NAME[1], 1);
		m_textures.emplace_back(normalMap);

		//メタリックスムースマップ。
		auto metallicSmoothMap = KaEngine::GetInstance()->GetTextureBank(metallicSmoothFilePath.c_str());
		if (metallicSmoothMap == nullptr) {
			metallicSmoothMap = new Texture;
			metallicSmoothMap->Init(metallicSmoothFilePath.c_str(), GL_TEXTURE_2D, 2, GL_RGBA, GL_UNSIGNED_BYTE);
			KaEngine::GetInstance()->RegistTextureBank(metallicSmoothFilePath.c_str(), metallicSmoothMap);
		}
		metallicSmoothMap->TexUnit(m_shaderProgram, TEXTURE_NAME[2], 2);
		m_textures.emplace_back(metallicSmoothMap);
	}

	void Material::Update()
	{
		m_shaderProgram->Activate();

		//テクスチャの割り当て。
		for (int i = 0; i < MAX_TEXTURE_NUM; ++i) {
			m_textures[i]->Bind(i);
		}
	}
}
