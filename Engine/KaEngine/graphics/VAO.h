#pragma once

namespace nsKaEngine {

	/// <summary>
	/// VertecArrayObject�B
	/// </summary>
	class VAO : Noncopyable
	{
	public:
		VAO();
		~VAO();

		/// <summary>
		/// �����������B
		/// </summary>
		void Init();

		/// <summary>
		/// �����̐ڑ��B
		/// </summary>
		/// <param name="vbo">VertexBuffer</param>
		/// <param name="layout">�֘A�t����ԍ�</param>
		/// <param name="numComponents">�T�C�Y</param>
		/// <param name="type">�C���q</param>
		/// <param name="stride">�֘A�t����\����</param>
		/// <param name="offset">�I�t�Z�b�g</param>
		void LinkAttribute(
			VBO& vbo,
			GLuint layout,
			GLuint numComponents,
			GLenum type,
			GLsizei sride,
			void* offset
		);
		/// <summary>
		/// �ڑ��B
		/// </summary>
		void Bind()
		{
			glBindVertexArray(m_id);
		}
		/// <summary>
		/// �����B
		/// </summary>
		void UnBind()
		{
			glBindVertexArray(0);
		}
		/// <summary>
		/// �폜�B
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
		GLuint m_id = 0;		//ID�B
	};
}