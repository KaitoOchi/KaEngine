#pragma once

#include "graphics/Texture.h"
#include "Camera.h"

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

		/// <summary>
		/// 初期化用のモデルデータ。
		/// </summary>
		struct ModelInitData
		{
			std::string fbxFilePath;
			std::string vertexShaderFilePath;
			std::string fragmentShaderFilePath;
			std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile = {""};
			void* expandUniformBuffer = nullptr;
			int expandUniformBufferSize = 0;
			std::string expandUniformBufferName;
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
			Ka_Assert(m_instance == nullptr, "codeError", "KaEngineクラスのインスタンスは一つしか作れません。");
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
			m_instance->Delete();
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

		/// <summary>
		/// 定数バッファバンクに登録。
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		void RegistUniformBufferBank(const char* uniformBufferName, GLuint* uniformBuffer)
		{
			m_uniformBufferBank.Regist(uniformBufferName, uniformBuffer);
		}

		/// <summary>
		/// バンクから定数バッファを取得。
		/// </summary>
		/// <param name="uniformBufferName"></param>
		/// <returns></returns>
		GLuint* GetUniformBufferBank(const char* uniformBufferName)
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
		static KaEngine* m_instance;				//インスタンス。

		FPSLimiter m_fpsLimiter;					//FPSリミッター。

		TResourceBank<Texture> m_textureBank;		//テクスチャバンク。
		TResourceBank<GLuint> m_shaderBank;			//シェーダーバンク。
		TResourceBank<GLuint> m_uniformBufferBank;	//定数バッファバンク。

		Texture* m_texture[3];
		std::vector<Texture*> m_textures;
		
		LightUB m_lightUB;

		Mesh m_floorMesh;
		Vector3 m_floorPos;
		Matrix m_floorModel;

		Mesh m_lightMesh;
		Vector3 m_lightPos;
		Matrix m_lightModel;

		Mesh m_pyramidMesh;
		Vector3 m_pyramidPos;
		Matrix m_pyramidModel;

		Sprite m_sprite;
		float m_timer = 0.0f;
	};
	extern Camera* g_camera3D;
}