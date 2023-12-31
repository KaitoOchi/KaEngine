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
			DirectionLightUB dirLig;
			PointLightUB ptLig;
			Vector3 eyePos;
			float pad;
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
		/// <summary>
		/// テクスチャバンクに登録。
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="texture"></param>
		void RegistTextureBank(const char* filePath, Texture* texture)
		{
			m_textureBank.Regist(filePath, texture);
		}

		/// <summary>
		/// バンクからテクスチャを取得。
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		Texture* GetTextureBank(const char* filePath)
		{
			return m_textureBank.Get(filePath);
		}

		/// <summary>
		/// シェーダーバンクに登録。
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="shader"></param>
		void RegistShaderBank(const char* filePath, GLuint* shader)
		{
			m_shaderBank.Regist(filePath, shader);
		}

		/// <summary>
		/// バンクからシェーダーを取得。
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

		TResourceBank<Texture> m_textureBank;	//テクスチャバンク。
		TResourceBank<GLuint> m_shaderBank;		//シェーダーバンク。
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