#include "KaEnginePreCompile.h"
#include "GraphicsEngine.h"

namespace nsKaEngine {

	GraphicsEngine* GraphicsEngine::m_instance = nullptr;

	void GraphicsEngine::Init(GLFWwindow* window)
	{
		m_window = window;

		m_frameBufferSize.Set(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);

		//Enable the Depth Buffer
		glEnable(GL_DEPTH_TEST);

		//backBufferとfrontBufferの切り替え。
		glfwSwapBuffers(window);

		//glfwMaximizeWindow(m_window);
	}

	void GraphicsEngine::Execute()
	{
		//ウィンドウサイズを取得。
		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		m_frameBufferSize.Set(static_cast<float>(width), static_cast<float>(height));
		glViewport(0, 0, width, height);
	}
}