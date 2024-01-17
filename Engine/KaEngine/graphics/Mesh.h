#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "ShaderClass.h"
#include "UniformBuffer.h"

namespace nsKaEngine {

	/// <summary>
	/// メッシュクラス。
	/// </summary>
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
			std::string fbxFilePath,
			std::string vertexShaderFile,
			std::string fragmentShaderFile,
			std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile,
			void* expandUniformBuffer,
			int expandUniformBufferSize,
			std::string expandUniformBufferName
		);

		/// <summary>
		/// 描画処理。
		/// </summary>
		void Draw(
			const Matrix& modelMatrix,
			const Matrix& viewMatrix,
			const Matrix& projectionMatrix
		);

		/// <summary>
		/// 削除処理。
		/// </summary>
		void Delete();

	private:
		std::vector<Vertex>		m_vertices;					//頂点情報。
		std::vector<GLuint>		m_indices;					//インデックス。
		std::vector<Texture>	m_textures;					//テクスチャ。
		VAO						m_vao;						//VertexArraysObject。
		VBO						m_vbo;						//VertexBufferObject。
		EBO						m_ebo;						//ElementsBufferObject。
		Shader					m_shaderProgram;			//シェーダー。
		UniformBuffer			m_modelUniformBuffer;		//モデル用UniformBufferObject。
		UniformBuffer			m_expandUniformBuffer;		//ユーザー拡張用UniformBufferObject。
		ModelUB					m_modelUB;					//モデル用構造体。
		void*					m_expandUB = nullptr;		//ユーザー拡張用構造体。
		int						m_expandUBSize = 0;			//構造体のサイズ。
	};
}

