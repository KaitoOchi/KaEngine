#include "KaEnginePreCompile.h"
#include "KaEngine.h"

#include <stb/stb_image.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

namespace nsKaEngine {

	KaEngine* KaEngine::m_instance = nullptr;
	Camera* g_camera3D = nullptr;				//3Dカメラ。

	//頂点座標。
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-50.5f, 0.0f,  50.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		-50.5f, 0.0f, -50.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 50.5f, 0.0f, -50.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 50.5f, 0.0f,  50.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

		-50.5f, 0.0f,  50.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		-50.5f, 0.0f, -50.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		 0.0f, 80.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

		-50.5f, 0.0f, -50.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 50.5f, 0.0f, -50.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.0f, 80.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

		 50.5f, 0.0f, -50.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 50.5f, 0.0f,  50.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.0f, 80.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

		 50.5f, 0.0f,  50.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		-50.5f, 0.0f,  50.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		 0.0f, 80.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-10.1f, -10.1f,  10.1f,
		-10.1f, -10.1f, -10.1f,
		 10.1f, -10.1f, -10.1f,
		 10.1f, -10.1f,  10.1f,
		-10.1f,  10.1f,  10.1f,
		-10.1f,  10.1f, -10.1f,
		 10.1f,  10.1f, -10.1f,
		 10.1f,  10.1f,  10.1f
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	KaEngine::KaEngine()
	{

	}

	KaEngine::~KaEngine()
	{

	}

	void KaEngine::Init(GLFWwindow* window)
	{
		g_camera3D = new Camera;
		g_camera3D->Init();

		m_window = window;

		//通常モデルの設定。
		m_shaderProgram = new Shader("Assets/shader/default.vert", "Assets/shader/default.frag");

		// Generates Vertex Array Object and binds it
		m_vao.Init();
		m_vao.Bind();

		// Generates Vertex Buffer Object and links it to vertices
		m_vbo.Init(vertices, sizeof(vertices));
		// Generates Element Buffer Object and links itt o indices
		m_ebo.Init(indices, sizeof(indices));

		// Links VBO to VAO
		m_vao.LinkAttribute(m_vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
		m_vao.LinkAttribute(m_vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		m_vao.LinkAttribute(m_vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		m_vao.LinkAttribute(m_vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		// UnBind all to prevent accidenally modifying them
		m_vao.UnBind();
		m_vbo.UnBind();
		m_ebo.UnBind();

		m_pyramidPos = Vector3(0.0f, 0.0f, 0.0f);
		m_pyramidModel.MakeTranslate(m_pyramidPos);

		m_lightPos = Vector3(100.0f, 100.0f, 100.0f);
		m_lightModel.MakeTranslate(m_lightPos);


		m_shaderProgram->Activate();
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(m_pyramidModel.mat));
		glUniform4f(glGetUniformLocation(m_shaderProgram->ID, "lightColor"), m_lightColor.x, m_lightColor.y, m_lightColor.z, m_lightColor.w);
		glUniform3f(glGetUniformLocation(m_shaderProgram->ID, "lightPos"), m_lightPos.x, m_lightPos.y, m_lightPos.z);

		//scene_block_index = glGetUniformBlockIndex(m_shaderProgram->ID, "ModelUB");
		//glUniformBlockBinding(m_shaderProgram->ID, scene_block_index, 0);
		//m_modelUniformBuffer.Init(&m_modelUB, sizeof(ModelUB));


		//ライト用モデルの設定。
		m_lightShader = new Shader("Assets/shader/light.vert", "Assets/shader/light.frag");
		m_lightVAO.Init();
		m_lightVAO.Bind();

		m_lightVBO.Init(lightVertices, sizeof(lightVertices));
		m_lightEBO.Init(lightIndices, sizeof(lightIndices));

		m_lightVAO.LinkAttribute(m_lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

		m_lightVAO.UnBind();
		m_lightVBO.UnBind();
		m_lightEBO.UnBind();

		m_lightShader->Activate();
		glUniformMatrix4fv(glGetUniformLocation(m_lightShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(m_lightModel.mat));
		glUniform4f(glGetUniformLocation(m_lightShader->ID, "lightColor"), m_lightColor.r, m_lightColor.g, m_lightColor.b, m_lightColor.a);

		//Texture
		m_albedoTexture.Init("Assets/sprite/test.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
		m_albedoTexture.TexUnit(m_shaderProgram, "g_albedoMap", 0);
		m_normalTexture.Init("Assets/sprite/planks.png", GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);
		m_normalTexture.TexUnit(m_shaderProgram, "g_normalMap", 1);

		//Enable the Depth Buffer
		glEnable(GL_DEPTH_TEST);

		//入力クラス。
		Input::CreateInstance(m_window);

		//backBufferとfrontBufferの切り替え。
		glfwSwapBuffers(window);
	}

	void KaEngine::Execute()
	{
		Input::GetInstance()->Update();
	}

	void KaEngine::BeginFrame()
	{
		m_fpsLimiter.BeginFrame();

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Clear the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void KaEngine::EndFrame()
	{
		Vector3 cameraPos = g_camera3D->GetPosition();

		// Tell OpenGL which Shader Proram we want to use
		m_shaderProgram->Activate();
		glUniform3f(glGetUniformLocation(m_shaderProgram->ID, "cameraPos"), cameraPos.x, cameraPos.y, cameraPos.z);
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(g_camera3D->GetViewProjectionMatrix().mat));

		//m_modelUB.mView = g_camera3D->GetViewProjectionMatrix().mat;
		//m_modelUniformBuffer.Update(0);

		// Binds Texture so that is appears in rendering
		m_albedoTexture.Bind();
		m_normalTexture.Bind();
		// Bind the VAO so OpenGL knows to use it
		m_vao.Bind();

		// Draw the triangles using the GL_TRIANGLES primive
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


		m_lightShader->Activate();
		glUniformMatrix4fv(glGetUniformLocation(m_lightShader->ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(g_camera3D->GetViewProjectionMatrix().mat));
		m_lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Swap the back buffer with the front buffer
		glfwSwapBuffers(m_window);
		glfwPollEvents();


		m_fpsLimiter.EndFrame();
		std::cout << m_fpsLimiter.Get() << "\n" << std::endl;
	}

	void KaEngine::Delete()
	{
		// Delete all the objects we've created
		m_vao.Delete();
		m_vbo.Delete();
		m_ebo.Delete();
		m_lightVAO.Delete();
		m_lightVBO.Delete();
		m_lightEBO.Delete();
		m_albedoTexture.Delete();
		m_normalTexture.Delete();
		m_shaderProgram->Delete();
		m_lightShader->Delete();
		delete m_shaderProgram;
		delete m_lightShader;
	}
}