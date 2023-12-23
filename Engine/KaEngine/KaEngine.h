#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "UniformBuffer.h"

namespace nsKaEngine {

	/// <summary>
	/// �G���W���N���X�B
	/// </summary>
	class KaEngine : Noncopyable
	{
	public:
		/// <summary>
		/// ���C�g�pUB�B
		/// </summary>
		struct LightUB
		{
			alignas(4) GLfloat ambient;
		};

		/// <summary>
		/// ���f���pUB�B
		/// </summary>
		struct ModelUB
		{
			alignas(64) Matrix mView;
		};

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
		/// <summary>
		/// 1�t���[���̊J�n�����B
		/// </summary>
		void BeginFrame();
		/// <summary>
		/// 1�t���[���̏I�������B
		/// </summary>
		void EndFrame();

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

		FPSLimiter m_fpsLimiter;			//FPS���~�b�^�[�B

		UniformBuffer m_modelUniformBuffer;
		ModelUB m_modelUB;
		GLuint scene_block_index = 0;

		Shader* m_shaderProgram = nullptr;
		VAO m_vao;
		VBO m_vbo;
		EBO m_ebo;
		Texture m_albedoTexture;
		Texture m_normalTexture;
		Texture m_metallicSmoothTexture;

		Shader* m_lightShader = nullptr;
		VAO m_lightVAO;
		VBO m_lightVBO;
		EBO m_lightEBO;

		Vector3 m_lightPos;
		Matrix m_lightModel;
		Vector3 m_pyramidPos;
		Matrix m_pyramidModel;
		Vector4 m_lightColor = Vector4::White;
	};
	extern Camera* g_camera3D;
}