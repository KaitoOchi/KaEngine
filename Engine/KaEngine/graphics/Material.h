#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �}�e���A���N���X�B
	/// </summary>
	class Material : Noncopyable
	{
	public:
		Material();
		~Material();

		/// <summary>
		/// �����������B
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

		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update();

		
		/// <summary>
		/// �V�F�[�_�[ID���擾�B
		/// </summary>
		/// <returns></returns>
		const GLuint GetShaderID() const
		{
			return m_shaderProgram->GetShaderID();
		}

		void ShaderActivate()
		{
			m_shaderProgram->Activate();
		}

	private:
		std::vector<Texture*>	m_textures;						//�e�N�X�`���B
		Shader*					m_shaderProgram = nullptr;		//�V�F�[�_�[�B
	};
}
