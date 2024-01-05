#include "KaEnginePreCompile.h"
#include "Mesh.h"

#include "UniformBuffer.h"

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

	}

	Mesh::~Mesh()
	{
		m_vao.Delete();
		m_vbo.Delete();
		m_ebo.Delete();
		m_shaderProgram.Delete();
	}

	void Mesh::Init(
		std::vector<Vertex>& vertices,
		std::vector<GLuint>& indices,
		std::vector<Texture>& textures,
		const char* vertexShaderFile,
		const char* fragmentShaderFile
	) {
		m_vertices = vertices;
		m_indices = indices;
		m_textures = textures;

		for (int i = 0; i < m_textures.size(); ++i) {
			m_textures[i].TexUnit(&m_shaderProgram, TEXTURE_NAME[i], i);
		}

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

		m_shaderProgram.Init(vertexShaderFile, fragmentShaderFile);
		m_shaderProgram.Activate();
		m_modelUniformBuffer.Init(sizeof(ModelUB), m_shaderProgram.ID, "ModelUB");
	}

	void Mesh::Draw(Matrix& modelMatrix)
	{
		m_shaderProgram.Activate();

		m_modelUB.mModel = modelMatrix;
		m_modelUB.mView = g_camera3D->GetViewMatrix();
		m_modelUB.mProj = g_camera3D->GetProjectionMatrix();
		m_modelUniformBuffer.Update(&m_modelUB, sizeof(ModelUB));

		m_vao.Bind();

		int textureSize = static_cast<int>(m_textures.size());
		for (int i = 0; i < textureSize; ++i) {
			m_textures[i].Bind();
		}

		// Draw the triangles using the GL_TRIANGLES primive
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
	}
}