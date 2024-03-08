#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �O���t�B�b�N�X�G���W���B
	/// </summary>
	class GraphicsEngine : Noncopyable
	{
	public:
		GraphicsEngine() {}
		~GraphicsEngine() {}

		/// <summary>
		/// �C���X�^���X�̍쐬�B
		/// </summary>
		static void CreateInstance(
			GLFWwindow* window,
			Config* deviceInfo
		) {
			Ka_Assert(m_instance == nullptr, "codeError", "GaphicsEngine�N���X�̃C���X�^���X�͈�������܂���B");
			m_instance = new GraphicsEngine;
			m_instance->Init(window, deviceInfo);
		}

		/// <summary>
		/// �C���X�^���X�̎擾�B
		/// </summary>
		/// <returns></returns>
		static GraphicsEngine* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// �C���X�^���X�̍폜�B
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
		}

	public:
		/// <summary>
		/// �E�B���h�E���擾�B
		/// </summary>
		/// <returns></returns>
		GLFWwindow* GetWindow() const
		{
			return m_window;
		}

		/// <summary>
		/// �E�B���h�E�T�C�Y���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector2& GetWindowSize() const
		{
			return m_frameBufferSize;
		}

		/// <summary>
		/// �t���X�N���[����Ԃ̐؂�ւ��B
		/// </summary>
		void ToggleFullScreen()
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			if (!m_isFullScreen) {
				m_frameBufferSize.Scale(1.2f);
				glfwSetWindowMonitor(m_window, monitor, 0, 0, static_cast<int>(m_frameBufferSize.x), static_cast<int>(m_frameBufferSize.y), GLFW_DONT_CARE);
				glViewport(0, 0, static_cast<int>(m_frameBufferSize.x), static_cast<int>(m_frameBufferSize.y));
			}
			else {
				m_frameBufferSize.Scale(0.8f);
				glfwSetWindowMonitor(m_window, NULL, 0, 35, static_cast<int>(m_frameBufferSize.x), static_cast<int>(m_frameBufferSize.y), GLFW_DONT_CARE);
				glViewport(0, 0, static_cast<int>(m_frameBufferSize.x), static_cast<int>(m_frameBufferSize.y));
			}
			m_isFullScreen = !m_isFullScreen;
		}

		/// <summary>
		/// ���s�����B
		/// </summary>
		void Execute();

		/// <summary>
		/// �����_�����O�R���e�L�X�g���擾�B
		/// </summary>
		/// <returns></returns>
		RenderContext& GetRenderContext()
		{
			return m_renderContext;
		}

		/// <summary>
		/// ���C�������_�[�^�[�Q�b�g���擾�B
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetRenderTarget()
		{
			return m_mainRenderTarget;
		}

		void Test();


	private:
		/// <summary>
		/// �����������B
		/// </summary>
		void Init(
			GLFWwindow* window,
			Config* deviceInfo
		);

	private:
		static GraphicsEngine*	m_instance;				//�C���X�^���X�B
		GLFWwindow*				m_window = nullptr;		//�E�B���h�E�B
		RenderContext			m_renderContext;		//�����_�����O�R���e�L�X�g�B

		RenderTarget			m_mainRenderTarget;		//�����_�[�^�[�Q�b�g�B
		Sprite					m_mainSprite;			//���C���摜�B
		Vector2					m_frameBufferSize;		//�E�B���h�E�T�C�Y�B
		bool					m_isFullScreen = false;	//�t���X�N���[�����ǂ����B
	};
}
