#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

namespace nsKaEngine {

	/// <summary>
	/// エンジンクラス。
	/// </summary>
	class KaEngine : Noncopyable
	{
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

		Shader* m_shaderProgram = nullptr;
		VAO m_vao;
		VBO m_vbo;
		EBO m_ebo;
		Texture m_testTexture;
	};
}