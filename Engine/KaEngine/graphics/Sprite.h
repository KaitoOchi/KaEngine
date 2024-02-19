#pragma once

namespace nsKaEngine {

	/// <summary>
	/// スプライト初期化用のデータ。
	/// </summary>
	struct SpriteInitData
	{
		std::string filePath;
		std::string vertexFilePath;
		std::string fragmentFilePath;
		std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile = { "" };
		int width = 0;
		int height = 0;
		void* expandUniformBuffer = nullptr;
		int expandUniformBufferSize = 0;
		std::string expandUniformBufferName;
	};

	/// <summary>
	/// スプライトクラス。
	/// </summary>
	class Sprite : Noncopyable
	{
	public:
		Sprite();
		~Sprite();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="initData"></param>
		void Init(SpriteInitData& initData);

		/// <summary>
		/// 更新処理。
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="rot">回転</param>
		/// <param name="scale">拡大率</param>
		/// <param name="pivot">ピボット</param>
		void Update(
			const Vector3& pos,
			const Quaternion& rot,
			const Vector3& scale,
			const Vector2& pivot
		);

		/// <summary>
		/// 描画処理。
		/// </summary>
		void Draw();

	private:
		/// <summary>
		/// テクスチャを作成。
		/// </summary>
		/// <param name="filePath"></param>
		void InitTexture(SpriteInitData& initData);
		/// <summary>
		/// VBOとEBOを作成。
		/// </summary>
		void InitVertexBufferAndElementsBuffer();
		/// <summary>
		/// シェーダーを作成。
		/// </summary>
		/// <param name="initData"></param>
		void InitShader(SpriteInitData& initData);
		/// <summary>
		/// 定数バッファを作成。
		/// </summary>
		/// <param name="initData"></param>
		void InitUniformBuffer(SpriteInitData& initData);

	private:
		/// <summary>
		/// スプライト用UB。
		/// </summary>
		struct SpriteUB
		{
			Matrix mvp;
			Vector4 mulColor;
		};

	private:
		std::vector<GLuint>	m_indices;						//インデックス。
		Shader				m_shaderProgram;				//シェーダープログラム。
		VAO					m_vao;							//VertexArraysObject。
		VBO					m_vbo;							//VertexBufferObject。
		EBO					m_ebo;							//ElementsBufferObject。
		Texture				m_texture;						//テクスチャ。
		UniformBuffer		m_spriteUniformBuffer;			//スプライト用UniformBufferObject。
		UniformBuffer		m_expandUniformBuffer;			//ユーザー拡張用UniformBufferObject。
		SpriteUB			m_spriteUB;						//スプライト用UB。
		Matrix				m_worldMatrix;					//ワールド行列。
		Vector4				m_mulColor = Vector4::White;	//乗算カラー。
		Vector2				m_size;							//画像のハーフサイズ。
		void*				m_expandUB = nullptr;			//ユーザー拡張用構造体。
		int					m_expandUBSize = 0;				//構造体のサイズ。
	};
}

