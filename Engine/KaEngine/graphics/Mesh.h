#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "ShaderClass.h"
#include "UniformBuffer.h"

namespace nsKaEngine {

	class Mesh : Noncopyable
	{
	public:
		/// <summary>
		/// モデル用UB。
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
		/// 初期化処理。
		/// </summary>
		/// <param name="vertices">頂点座標</param>
		/// <param name="indices">インデックス</param>
		/// <param name="textures">テクスチャ</param>
		void Init(
			std::vector<Vertex>& vertices,
			std::vector<GLuint>& indices,
			std::vector<Texture>& textures,
			const char* vertexShaderFile,
			const char* fragmentShaderFile
		);

		/// <summary>
		/// 描画処理。
		/// </summary>
		void Draw(Matrix& modelMatrix);

		void ShaderActivate()
		{
			m_shaderProgram.Activate();
		}

		GLuint GetShaderID()
		{
			return m_shaderProgram.ID;
		}

	private:
		std::vector<Vertex>		m_vertices;
		std::vector<GLuint>		m_indices;
		std::vector<Texture>	m_textures;
		VAO m_vao;
		VBO m_vbo;
		EBO m_ebo;
		Shader m_shaderProgram;
		UniformBuffer m_modelUniformBuffer;
		ModelUB m_modelUB;
	};
}

