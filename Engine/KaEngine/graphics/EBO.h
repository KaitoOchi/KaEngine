#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ElementBufferObject�B
	/// </summary>
	class EBO : Noncopyable
	{
	public:
		EBO();
		~EBO();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="indices"></param>
		void Init(std::vector<GLuint>& indices);
		/// <summary>
		/// �ڑ��B
		/// </summary>
		void Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}
		/// <summary>
		/// �����B
		/// </summary>
		void UnBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		/// <summary>
		/// �폜�B
		/// </summary>
		void Delete()
		{
			glDeleteBuffers(1, &m_id);
		}

	private:
		GLuint m_id = 0;		//ID�B
	};
}