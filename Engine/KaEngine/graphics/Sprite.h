#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �X�v���C�g�������p�̃f�[�^�B
	/// </summary>
	struct SpriteInitData
	{
		std::string filePath;
		std::string vertexFilePath;
		std::string fragmentFilePath;
		std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile = { "" };
		int width = 0;
		int height = 0;
		void* expandUniformBuffer = nullptr;
		int expandUniformBufferSize = 0;
		std::string expandUniformBufferName;
	};

	/// <summary>
	/// �X�v���C�g�N���X�B
	/// </summary>
	class Sprite : Noncopyable
	{
	public:
		Sprite();
		~Sprite();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="initData"></param>
		void Init(SpriteInitData& initData);

		/// <summary>
		/// �X�V�����B
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		/// <param name="pivot">�s�{�b�g</param>
		void Update(
			const Vector3& pos,
			const Quaternion& rot,
			const Vector3& scale,
			const Vector2& pivot
		);

		/// <summary>
		/// �`�揈���B
		/// </summary>
		void Draw();

	private:
		/// <summary>
		/// �e�N�X�`�����쐬�B
		/// </summary>
		/// <param name="filePath"></param>
		void InitTexture(SpriteInitData& initData);
		/// <summary>
		/// VBO��EBO���쐬�B
		/// </summary>
		void InitVertexBufferAndElementsBuffer();
		/// <summary>
		/// �V�F�[�_�[���쐬�B
		/// </summary>
		/// <param name="initData"></param>
		void InitShader(SpriteInitData& initData);
		/// <summary>
		/// �萔�o�b�t�@���쐬�B
		/// </summary>
		/// <param name="initData"></param>
		void InitUniformBuffer(SpriteInitData& initData);

	private:
		/// <summary>
		/// �X�v���C�g�pUB�B
		/// </summary>
		struct SpriteUB
		{
			Matrix mvp;
			Vector4 mulColor;
		};

	private:
		std::vector<GLuint>	m_indices;						//�C���f�b�N�X�B
		Shader				m_shaderProgram;				//�V�F�[�_�[�v���O�����B
		VAO					m_vao;							//VertexArraysObject�B
		VBO					m_vbo;							//VertexBufferObject�B
		EBO					m_ebo;							//ElementsBufferObject�B
		Texture				m_texture;						//�e�N�X�`���B
		UniformBuffer		m_spriteUniformBuffer;			//�X�v���C�g�pUniformBufferObject�B
		UniformBuffer		m_expandUniformBuffer;			//���[�U�[�g���pUniformBufferObject�B
		SpriteUB			m_spriteUB;						//�X�v���C�g�pUB�B
		Matrix				m_worldMatrix;					//���[���h�s��B
		Vector4				m_mulColor = Vector4::White;	//��Z�J���[�B
		Vector2				m_size;							//�摜�̃n�[�t�T�C�Y�B
		void*				m_expandUB = nullptr;			//���[�U�[�g���p�\���́B
		int					m_expandUBSize = 0;				//�\���̂̃T�C�Y�B
	};
}

