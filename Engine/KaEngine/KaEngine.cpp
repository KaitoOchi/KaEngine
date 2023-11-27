#include "KaEnginePreCompile.h"
#include "KaEngine.h"

#include <stb/stb_image.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

namespace nsKaEngine {

	KaEngine* KaEngine::m_instance = nullptr;

	//頂点座標。
	GLfloat vertices[] =
	{// 	COORNATES			/			COLORS			/	  TEXCOORD		//
		-0.5f,  0.0f,  0.5f,		0.83f, 0.70f,  0.44f,		0.0f, 0.0f,
		-0.5f,  0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		5.0f, 0.0f,
		 0.5f,  0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		0.0f, 0.0f,
		 0.5f,  0.0f,  0.5f,		0.83f, 0.70f,  0.44f,		5.0f, 0.0f,
		 0.0f,  0.8f,  0.0f,		0.92f, 0.86f,  0.76f,		2.5f, 5.0f
	};

	//インデックス。
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	KaEngine::KaEngine()
	{

	}

	KaEngine::~KaEngine()
	{

	}

	void KaEngine::Init(GLFWwindow* window)
	{
		m_window = window;

		gladLoadGL(glfwGetProcAddress);
		glViewport(0, 0, static_cast<int>(FRAME_BUFFER_WIDTH), static_cast<int>(FRAME_BUFFER_HEIGHT));

		// Generates Shader object using shades default.vert and default.frag
		m_shaderProgram = new Shader("Assets/shader/default.vert", "Assets/shader/default.frag");

		// Generates Vertex Array Object and binds it
		m_vao.Init();
		m_vao.Bind();

		// Generates Vertex Buffer Object and links it to vertices
		m_vbo.Init(vertices, sizeof(vertices));
		// Generates Element Buffer Object and links itt o indices
		m_ebo.Init(indices, sizeof(indices));

		// Links VBO to VAO
		m_vao.LinkAttribute(m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		m_vao.LinkAttribute(m_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		m_vao.LinkAttribute(m_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		// UnBind all to prevent accidenally modifying them
		m_vao.UnBind();
		m_vbo.UnBind();
		m_ebo.UnBind();


		//Texture
		m_testTexture.Init("Assets/sprite/test.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		m_testTexture.TexUnit(m_shaderProgram, "tex0", 0);

		//Enable the Depth Buffer
		glEnable(GL_DEPTH_TEST);

		//入力クラス。
		Input::CreateInstance(m_window);


		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//backBufferとfrontBufferの切り替え。
		glfwSwapBuffers(window);
	}

	void KaEngine::Execute()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Clear the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Proram we want to use
		m_shaderProgram->Activate();


		Input::GetInstance()->Update();

		// Binds Texture so that is appears in rendering
		m_testTexture.Bind();
		// Bind the VAO so OpenGL knows to use it
		m_vao.Bind();
		// Draw the triangles using the GL_TRIANGLES primive
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//Swap the back buffer with the front buffer
		glfwSwapBuffers(m_window);

		glfwPollEvents();

	}

	void KaEngine::Delete()
	{
		// Delete all the objects we've created
		m_vao.Delete();
		m_vbo.Delete();
		m_ebo.Delete();
		m_testTexture.Delete();
		m_shaderProgram->Delete();
		delete m_shaderProgram;
	}
}