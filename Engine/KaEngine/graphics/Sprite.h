#pragma once

namespace nsKaEngine {

	/// <summary>
	/// スプライト初期化用のデータ。
	/// </summary>
	struct SpriteInitData
	{
		std::string filePath;															//ファイルパス。
		std::string vertexFilePath;														//頂点シェーダーのファイルパス。
		std::string fragmentFilePath;													//フラグメントシェーダーのファイルパス。
		std::array<Texture*, ADD_INCLUDE_FILE_MAX> textures = { nullptr };				//テクスチャ。
		std::array<std::string, ADD_INCLUDE_FILE_MAX> addIncludeFile = { "" };			//追加のインクルードファイル。
		int width = 0;																	//横幅。
		int height = 0;																	//高さ。
		void* expandUniformBuffer = nullptr;											//ユーザー拡張の定数バッファ。
		int expandUniformBufferSize = 0;												//定数バッファのサイズ。
		std::string expandUniformBufferName;											//定数バッファの名前。
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
		/// 乗算カラーを設定。
		/// </summary>
		/// <param name="color"></param>
		void SetMulColor(const Vector4& color)
		{
			m_mulColor = color;
		}

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
		void Draw(RenderContext& rc);

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
			Matrix mvp;			//ワールド行列。
			Vector4 mulColor;	//乗算カラー。
		};

	private:
		std::vector<GLuint>	m_indices;						//インデックス。
		Shader*				m_shaderProgram = nullptr;		//シェーダープログラム。
		VAO					m_vao;							//VertexArraysObject。
		VBO					m_vbo;							//VertexBufferObject。
		EBO					m_ebo;							//ElementsBufferObject。
		Texture*			m_texture[8];					//テクスチャ。
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
