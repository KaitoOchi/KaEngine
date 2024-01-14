#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ユニフォームバッファ。
	/// </summary>
	class UniformBuffer
	{
	public:
		UniformBuffer();
		~UniformBuffer();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="size">構造体のサイズ</param>
		/// <param name="shaderID">シェーダープログラムID</param>
		/// <param name="blockName">シェーダーでつけられている構造体の名前</param>
		void Init(
			const int size,
			GLuint shaderID,
			const char* blockName
		);

		/// <summary>
		/// 更新処理。
		/// </summary>
		/// <param name="data">構造体</param>
		/// <param name="size">構造体のサイズ</param>
		void Update(void* data, const int size);

	private:
		GLuint m_ubo = 0;				//UBO。
		GLuint m_blockIndex = 0;		//ブロックインデックス。
	};
}

