#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "UniformBuffer.h"

#include "graphics/light/DirectionLight.h"
#include "graphics/light/PointLight.h"
#include "timer/FPSLimiter.h"
#include "graphics/Mesh.h"

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
			DirectionLightUB dirLig;
			PointLightUB ptLig;
			Vector3 eyePos;
			float pad;
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
		/// <summary>
		/// �e�N�X�`���o���N�ɓo�^�B
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="texture"></param>
		void RegistTextureBank(const char* filePath, Texture* texture)
		{
			m_textureBank.Regist(filePath, texture);
		}

		/// <summary>
		/// �o���N����e�N�X�`�����擾�B
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		Texture* GetTextureBank(const char* filePath)
		{
			return m_textureBank.Get(filePath);
		}

		/// <summary>
		/// �V�F�[�_�[�o���N�ɓo�^�B
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="shader"></param>
		void RegistShaderBank(const char* filePath, GLuint* shader)
		{
			m_shaderBank.Regist(filePath, shader);
		}

		/// <summary>
		/// �o���N����V�F�[�_�[���擾�B
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		GLuint* GetShaderBank(const char* filePath)
		{
			return m_shaderBank.Get(filePath);
		}

		void RegistUniformBufferBank(const char* uniformBufferName, UniformBuffer* uniformBuffer)
		{
			m_uniformBufferBank.Regist(uniformBufferName, uniformBuffer);
		}

		UniformBuffer* GetUniformBufferBank(const char* uniformBufferName)
		{
			return m_uniformBufferBank.Get(uniformBufferName);
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

		TResourceBank<Texture> m_textureBank;	//�e�N�X�`���o���N�B
		TResourceBank<GLuint> m_shaderBank;		//�V�F�[�_�[�o���N�B
		TResourceBank<UniformBuffer> m_uniformBufferBank;

		UniformBuffer m_lightUniformBuffer;
		LightUB m_lightUB;

		Mesh m_floorMesh;
		Texture m_textures[3];
		Vector3 m_floorPos;
		Matrix m_floorModel;

		Mesh m_lightMesh;
		Vector3 m_lightPos;
		Matrix m_lightModel;

		Mesh m_pyramidMesh;
		Vector3 m_pyramidPos;
		Matrix m_pyramidModel;
	};
	extern Camera* g_camera3D;
}