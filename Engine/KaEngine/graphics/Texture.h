#pragma once
#include <stb/stb_image.h>
#include "ShaderClass.h"

namespace nsKaEngine {

	/// <summary>
	/// テクスチャー。
	/// </summary>
	class Texture : Noncopyable
	{
	public:
		Texture();
		~Texture();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="image">ファイルパス。</param>
		/// <param name="texType">テクスチャーの種類</param>
		/// <param name="slot">スロット番号</param>
		/// <param name="format">フォーマット</param>
		/// <param name="pixelType">ピクセルの種類</param>
		void Init(
			const char* image,
			const GLenum texType,
			const GLuint slot,
			const GLenum format,
			const GLenum pixelType
		);

		/// <summary>
		/// レンダーテクスチャを作成。
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="mipLevel"></param>
		/// <param name="format"></param>
		void InitRenderTexture(
			const int width,
			const int height,
			const GLuint mipLevel,
			const GLenum format
		);

		/// <summary>
		/// シェーダーに送信。
		/// </summary>
		/// <param name="shader">シェーダー</param>
		/// <param name="uniform">変数名</param>
		/// <param name="slot">スロット番号</param>
		void TexUnit(
			const Shader* shader, 
			const char* uniform,
			const GLuint slot
		);

		/// <summary>
		/// テクスチャーIDを取得。
		/// </summary>
		/// <returns></returns>
		const GLuint GetTextureID() const
		{
			return m_id;
		}

		/// <summary>
		/// 接続。
		/// </summary>
		void Bind(const GLuint slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(m_target, m_id);
		}

		/// <summary>
		/// 解除。
		/// </summary>
		void UnBind()
		{
			glBindTexture(m_target, 0);
		}

		/// <summary>
		/// 削除。
		/// </summary>
		void Delete()
		{
			glDeleteTextures(1, &m_id);
		}

	private:
		GLuint m_id = 0;		//テクスチャーID。
		GLenum m_target = 0;	//テクスチャーの種類。
	};
}