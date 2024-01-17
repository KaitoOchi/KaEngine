#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "ShaderClass.h"
#include "UniformBuffer.h"

namespace nsKaEngine {

	/// <summary>
	/// ���b�V���N���X�B
	/// </summary>
	class Mesh : Noncopyable
	{
	public:
		/// <summary>
		/// ���f���pUB�B
		/// </summary>
		struct ModelUB
		{
			Matrix mModel;
			Matrix mView;
			Matrix mProj;
		};
	public:
		Mesh();
		~Mesh();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="vertices">���_���W</param>
		/// <param name="indices">�C���f�b�N�X</param>
		/// <param name="textures">�e�N�X�`��</param>
		void Init(
			std::vector<Vertex>& vertices,
			std::vector<GLuint>& indices,
			std::vector<Texture>& textures,
			std::string fbxFilePath,
			std::string vertexShaderFile,
			std::string fragmentShaderFile,
			std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile,
			void* expandUniformBuffer,
			int expandUniformBufferSize,
			std::string expandUniformBufferName
		);

		/// <summary>
		/// �`�揈���B
		/// </summary>
		void Draw(
			const Matrix& modelMatrix,
			const Matrix& viewMatrix,
			const Matrix& projectionMatrix
		);

		/// <summary>
		/// �폜�����B
		/// </summary>
		void Delete();

	private:
		std::vector<Vertex>		m_vertices;					//���_���B
		std::vector<GLuint>		m_indices;					//�C���f�b�N�X�B
		std::vector<Texture>	m_textures;					//�e�N�X�`���B
		VAO						m_vao;						//VertexArraysObject�B
		VBO						m_vbo;						//VertexBufferObject�B
		EBO						m_ebo;						//ElementsBufferObject�B
		Shader					m_shaderProgram;			//�V�F�[�_�[�B
		UniformBuffer			m_modelUniformBuffer;		//���f���pUniformBufferObject�B
		UniformBuffer			m_expandUniformBuffer;		//���[�U�[�g���pUniformBufferObject�B
		ModelUB					m_modelUB;					//���f���p�\���́B
		void*					m_expandUB = nullptr;		//���[�U�[�g���p�\���́B
		int						m_expandUBSize = 0;			//�\���̂̃T�C�Y�B
	};
}

