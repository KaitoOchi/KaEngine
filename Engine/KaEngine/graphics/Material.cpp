#include "KaEnginePreCompile.h"
#include "Material.h"

namespace nsKaEngine {

	void Material::Init(
		const char* albedoFilePath,
		const char* normalFilePath,
		const char* metallicSmoothFilePath,
		const char* vsFilePath,
		const char* fsFilePath
	) {
		//アルベドマップ。
		auto albedoMap = KaEngine::GetInstance()->GetTextureBank(albedoFilePath);

		if (albedoMap == nullptr) {
			albedoMap = new Texture();
			albedoMap->Init(albedoFilePath, GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
			KaEngine::GetInstance()->RegistTextureBank(albedoFilePath, albedoMap);
		}

		//m_albedoMap = albedoMap;
	}
}