#pragma once

namespace nsKaEngine {

	/// <summary>
	/// VertecArrayObject。
	/// </summary>
	class VAO : Noncopyable
	{
	public:
		VAO();
		~VAO();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		void Init();

		/// <summary>
		/// 属性の接続。
		/// </summary>
		/// <param name="vbo">VertexBuffer</param>
		/// <param name="layout">関連付ける番号</param>
		/// <param name="numComponents">サイズ</param>
		/// <param name="type">修飾子</param>
		/// <param name="stride">関連付ける構造体</param>
		/// <param name="offset">オフセット</param>
		void LinkAttribute(
			VBO& vbo,
			GLuint layout,
			GLuint numComponents,
			GLenum type,
			GLsizei sride,
			void* offset
		);
		/// <summary>
		/// 接続。
		/// </summary>
		void Bind()
		{
			glBindVertexArray(m_id);
		}
		/// <summary>
		/// 解除。
		/// </summary>
		void UnBind()
		{
			glBindVertexArray(0);
		}
		/// <summary>
		/// 削除。
		/// </summary>
		void Delete()
		{
			glDeleteVertexArrays(1, &m_id);
		}

		const GLuint GetID() const
		{
			return m_id;
		}

	private:
		GLuint m_id = 0;		//ID。
	};
}