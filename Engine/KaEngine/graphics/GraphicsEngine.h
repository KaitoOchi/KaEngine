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
		static void CreateInstance(GLFWwindow* window)
		{
			Ka_Assert(m_instance == nullptr, "codeError", "GaphicsEngine�N���X�̃C���X�^���X�͈�������܂���B");
			m_instance = new GraphicsEngine;
			m_instance->Init(window);
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
		/// �E�B���h�E�̌Œ��L�����B
		/// </summary>
		void ActiveFixedWindow()
		{
			int w = static_cast<int>(m_frameBufferSize.x);
			int h = static_cast<int>(m_frameBufferSize.y);
			glfwSetWindowSizeLimits(m_window, w, h, w, h);
		}

		/// <summary>
		/// �E�B���h�E�̌Œ�𖳌����B
		/// </summary>
		void DeactiveFixedWindow()
		{
			glfwSetWindowSizeLimits(m_window, 0, 0, static_cast<int>(m_frameBufferSize.x), static_cast<int>(m_frameBufferSize.y));
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
		/// ���s�����B
		/// </summary>
		void Execute();


	private:
		/// <summary>
		/// �����������B
		/// </summary>
		void Init(GLFWwindow* window);

	private:
		static GraphicsEngine*	m_instance;				//�C���X�^���X�B
		GLFWwindow*				m_window = nullptr;		//�E�B���h�E�B
		Vector2					m_frameBufferSize;		//�E�B���h�E�T�C�Y�B

	};
}