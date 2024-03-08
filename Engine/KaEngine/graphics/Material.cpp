	#include "KaEnginePreCompile.h"
#include "Material.h"
#include "Texture.h"

namespace nsKaEngine {

	Material::Material()
	{

	}

	Material::~Material()
	{
		m_shaderProgram.Delete();
	}

	void Material::Init(
		std::string albedoFilePath,
		std::string normalFilePath,
		std::string metallicSmoothFilePath,
		std::string vsFilePath,
		std::string fsFilePath,
		std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile
	) {
		//アルベドマップ。
		m_albedoMap = KaEngine::GetInstance()->GetTextureBank(albedoFilePath.c_str());
		if (m_albedoMap == nullptr) {
			m_albedoMap = new Texture;
			m_albedoMap->Init(albedoFilePath.c_str(), GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
			KaEngine::GetInstance()->RegistTextureBank(albedoFilePath.c_str(), m_albedoMap);
		}

		//法線マップ。
		m_normalMap = KaEngine::GetInstance()->GetTextureBank(normalFilePath.c_str());
		if (m_normalMap == nullptr) {
			m_normalMap = new Texture;
			m_normalMap->Init(normalFilePath.c_str(), GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);
			KaEngine::GetInstance()->RegistTextureBank(normalFilePath.c_str(), m_normalMap);
		}

		//メタリックスムースマップ。
		m_metallicSmoothMap = KaEngine::GetInstance()->GetTextureBank(metallicSmoothFilePath.c_str());
		if (m_metallicSmoothMap == nullptr) {
			m_metallicSmoothMap = new Texture;
			m_metallicSmoothMap->Init(metallicSmoothFilePath.c_str(), GL_TEXTURE_2D, 2, GL_RGBA, GL_UNSIGNED_BYTE);
			KaEngine::GetInstance()->RegistTextureBank(metallicSmoothFilePath.c_str(), m_metallicSmoothMap);
		}

		//シェーダーの設定。
		m_shaderProgram.Init(vsFilePath.c_str(), fsFilePath.c_str(), addIncludeFile);
		m_shaderProgram.Activate();
	}
}