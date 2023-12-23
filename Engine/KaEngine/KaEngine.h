#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "UniformBuffer.h"

namespace nsKaEngine {

	/// <summary>
	/// エンジンクラス。
	/// </summary>
	class KaEngine : Noncopyable
	{
	public:
		/// <summary>
		/// ライト用UB。
		/// </summary>
		struct LightUB
		{
			alignas(4) GLfloat ambient;
		};

		/// <summary>
		/// モデル用UB。
		/// </summary>
		struct ModelUB
		{
			alignas(64) Matrix mView;
		};

	public:
		KaEngine();
		~KaEngine();

		/// <summary>
		/// インスタンスの作成。
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
		/// インスタンスの取得。
		/// </summary>
		/// <returns></returns>
		static KaEngine* GetInstance()
		{
			return m_instance;
		}

		/// <summary>
		/// インスタンスの削除。
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
		/// 実行処理。
		/// </summary>
		void Execute();
		/// <summary>
		/// 1フレームの開始処理。
		/// </summary>
		void BeginFrame();
		/// <summary>
		/// 1フレームの終了処理。
		/// </summary>
		void EndFrame();

	private:
		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="window"></param>
		void Init(GLFWwindow* window);
		/// <summary>
		/// 削除処理。
		/// </summary>
		void Delete();

	private:
		static KaEngine* m_instance;		//インスタンス。

		GLFWwindow* m_window = nullptr;		//ウィンドウ。

		FPSLimiter m_fpsLimiter;			//FPSリミッター。

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