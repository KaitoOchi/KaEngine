#pragma once

namespace nsKaEngine {

	/// <summary>
	/// 頂点情報。
	/// </summary>
	struct Vertex
	{
		Vector3 position = Vector3::Zero;
		Vector3 normal = Vector3::Zero;
		Vector3 color = Vector3::Zero;
		Vector2 uv = Vector2::Zero;
	};

	/// <summary>
	/// スプライト用頂点情報。
	/// </summary>
	struct SpriteVertex {
		Vector4 pos;
		Vector2 uv;
	};

	/// <summary>
	/// VertexBufferObject。
	/// </summary>
	class VBO : Noncopyable
	{
	public:
		VBO();
		~VBO();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="vertices">頂点情報</param>
		void Init(std::vector<Vertex>& vertices);
		void Init(std::vector<SpriteVertex>& vertices);

		/// <summary>
		/// 接続。
		/// </summary>
		void Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}
		/// <summary>
		/// 解除。
		/// </summary>
		void UnBind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		/// <summary>
		/// 削除。
		/// </summary>
		void Delete()
		{
			glDeleteBuffers(1, &m_id);
		}

	private:
		GLuint m_id = 0;	//ID。
	};
}
