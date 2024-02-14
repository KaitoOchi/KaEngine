#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ���_���B
	/// </summary>
	struct Vertex
	{
		Vector3 position = Vector3::Zero;
		Vector3 normal = Vector3::Zero;
		Vector3 color = Vector3::Zero;
		Vector2 uv = Vector2::Zero;
	};

	/// <summary>
	/// �X�v���C�g�p���_���B
	/// </summary>
	struct SpriteVertex {
		Vector4 pos;
		Vector2 uv;
	};

	/// <summary>
	/// VertexBufferObject�B
	/// </summary>
	class VBO : Noncopyable
	{
	public:
		VBO();
		~VBO();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="vertices">���_���</param>
		void Init(std::vector<Vertex>& vertices);
		void Init(std::vector<SpriteVertex>& vertices);

		/// <summary>
		/// �ڑ��B
		/// </summary>
		void Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}
		/// <summary>
		/// �����B
		/// </summary>
		void UnBind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		/// <summary>
		/// �폜�B
		/// </summary>
		void Delete()
		{
			glDeleteBuffers(1, &m_id);
		}

	private:
		GLuint m_id = 0;	//ID�B
	};
}
