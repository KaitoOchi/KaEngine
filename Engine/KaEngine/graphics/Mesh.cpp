#include "KaEnginePreCompile.h"
#include "Mesh.h"

namespace nsKaEngine {

	namespace
	{
		const char* TEXTURE_NAME[3] = { "g_albedoMap",
										"g_normalMap",
										"g_metallicSmoothMap"
									};
	}

	Mesh::Mesh()
	{
		m_textures.reserve(3);
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::Init(
		std::vector<Vertex>& vertices,
		std::vector<GLuint>& indices,
		std::vector<Texture*>& textures,
		std::string fbxFilePath,
		std::string vertexShaderFile,
		std::string fragmentShaderFile,
		std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile,
		void* expandUniformBuffer,
		int expandUniformBufferSize,
		std::string expandUniformBufferName
	) {
		m_vertices = vertices;
		m_indices = indices;

		// Generates Vertex Array Object and binds it
		m_vao.Init();
		m_vao.Bind();

		// Generates Vertex Buffer Object and links it to vertices
		m_vbo.Init(vertices);
		// Generates Element Buffer Object and links itt o indices
		m_ebo.Init(indices);

		// Links VBO to VAO
		m_vao.LinkAttribute(m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		m_vao.LinkAttribute(m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		m_vao.LinkAttribute(m_vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		m_vao.LinkAttribute(m_vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

		// UnBind all to prevent accidenally modifying them
		m_vao.UnBind();
		m_vbo.UnBind();
		m_ebo.UnBind();

		//シェーダーの設定。
		m_shaderProgram.Init(vertexShaderFile.c_str(), fragmentShaderFile.c_str(), addIncludeFile);
		m_shaderProgram.Activate();

		//テクスチャの設定。
		for (int i = 0; i < textures.size(); ++i)
		{
			m_textures.emplace_back(textures[i]);
			m_textures[i]->TexUnit(&m_shaderProgram, TEXTURE_NAME[i], i);
		}

		//定数バッファの設定。
		m_modelUniformBuffer.Init(sizeof(ModelUB), m_shaderProgram.GetShaderID(), "ModelUB");
		if (expandUniformBuffer != nullptr) {
			m_expandUniformBuffer.Init(expandUniformBufferSize, m_shaderProgram.GetShaderID(), expandUniformBufferName.c_str());
			m_expandUB = expandUniformBuffer;
			m_expandUBSize = expandUniformBufferSize;
		}
	}

	void Mesh::Draw(
		const Matrix& modelMatrix,
		const Matrix& viewMatrix,
		const Matrix& projectionMatrix
	) {
		//モデル用UniformBufferの更新。
		m_modelUB.mModel = modelMatrix;
		m_modelUB.mView = viewMatrix;
		m_modelUB.mProj = projectionMatrix;

		m_shaderProgram.Activate();
		m_modelUniformBuffer.Update(&m_modelUB, sizeof(ModelUB));

		if (m_expandUB != nullptr) {
			m_expandUniformBuffer.Update(m_expandUB, m_expandUBSize);
		}

		m_vao.Bind();

		int textureSize = static_cast<int>(m_textures.size());
		for (int i = 0; i < textureSize; ++i) {
			m_textures[i]->Bind(i);
		}

		// Draw the triangles using the GL_TRIANGLES primive
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
	}

	void Mesh::Delete()
	{
		m_vao.Delete();
		m_vbo.Delete();
		m_ebo.Delete();
		m_shaderProgram.Delete();
	}
}