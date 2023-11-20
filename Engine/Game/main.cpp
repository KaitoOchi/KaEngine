#include "stdafx.h"

#include <stb/stb_image.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

const float FRAME_BUFFER_WIDTH = 1600.0f;
const float FRAME_BUFFER_HEIGHT = 900.0f;

int main()
{

	//GLFWの初期化。
	glfwInit();

	//GLFWのバージョンとプロファイルを指定。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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


	//ウィンドウを作成。
	GLFWwindow* window = glfwCreateWindow(static_cast<int>(FRAME_BUFFER_WIDTH), static_cast<int>(FRAME_BUFFER_HEIGHT), "Game", NULL, NULL);

	if (window == NULL) {
		std::cout << "GLFWのウィンドウ作成に失敗しました。" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL(glfwGetProcAddress);
	glViewport(0, 0, static_cast<int>(FRAME_BUFFER_WIDTH), static_cast<int>(FRAME_BUFFER_HEIGHT));

	// Generates Shader object using shades default.vert and default.frag
	Shader* shaderProgram;
	shaderProgram = new Shader("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links itt o indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// UnBind all to prevent accidenally modifying them
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();


	//Texture
	Texture testTexture("test.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	testTexture.TexUnit(shaderProgram, "tex0", 0);

	//Enable the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	//カメラクラス。
	Camera camera(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, shaderProgram);

	//入力クラス。
	Input::CreateInstance(window);


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//backBufferとfrontBufferの切り替え。
	glfwSwapBuffers(window);


	//メインのループ処理。
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Clear the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Proram we want to use
		shaderProgram->Activate();


		Input::GetInstance()->Update();

		Vector3 axis;
		axis = Input::GetInstance()->GetMouseAxis();

		Vector3 pos;
		pos = Input::GetInstance()->GetMousePosition();

		if (Input::GetInstance()->GetKey(enButtonW)) {
			axis = axis;
		}


		camera.Input();
		camera.Update();

		// Binds Texture so that is appears in rendering
		testTexture.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangles using the GL_TRIANGLES primive
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	testTexture.Delete();
	shaderProgram->Delete();

	delete shaderProgram;

	//GLFWの終了処理。
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}