#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ElementBufferObject。
	/// </summary>
	class EBO : Noncopyable
	{
	public:
		EBO();
		~EBO();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="indices"></param>
		void Init(std::vector<GLuint>& indices);
		/// <summary>
		/// 接続。
		/// </summary>
		void Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}
		/// <summary>
		/// 解除。
		/// </summary>
		void UnBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		/// <summary>
		/// 削除。
		/// </summary>
		void Delete()
		{
			glDeleteBuffers(1, &m_id);
		}

	private:
		GLuint m_id = 0;		//ID。
	};
}