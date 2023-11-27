#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

namespace nsKaEngine {

	/// <summary>
	/// �G���W���N���X�B
	/// </summary>
	class KaEngine : Noncopyable
	{
	public:
		KaEngine();
		~KaEngine();

		/// <summary>
		/// �C���X�^���X�̍쐬�B
		/// </summary>
		/// <param name="window"></param>
		static void CreateInstance(GLFWwindow* window)
		{
			if (m_instance != nullptr) {
				std::abort();
			}
			m_instance = new KaEngine;

			m_instance->Init(window);
		}

		/// <summary>
		/// �C���X�^���X�̎擾�B
		/// </summary>
		/// <returns></returns>
		static KaEngine* GetInstance()
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
		Shader* GetShader()
		{
			return m_shaderProgram;
		}

		/// <summary>
		/// ���s�����B
		/// </summary>
		void Execute();

	private:
		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="window"></param>
		void Init(GLFWwindow* window);

		/// <summary>
		/// �폜�����B
		/// </summary>
		void Delete();

	private:
		static KaEngine* m_instance;		//�C���X�^���X�B

		GLFWwindow* m_window = nullptr;		//�E�B���h�E�B

		Shader* m_shaderProgram = nullptr;
		VAO m_vao;
		VBO m_vbo;
		EBO m_ebo;
		Texture m_testTexture;
	};
}