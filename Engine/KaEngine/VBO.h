#pragma once

namespace nsKaEngine {

	/// <summary>
	/// í∏ì_èÓïÒÅB
	/// </summary>
	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector3 color;
		Vector2 uv;
	};

	class VBO
	{
	public:
		// Reference ID of the Vertex Buffer Object
		GLuint ID;

		VBO();
		~VBO();

		// generates a Vertex Buffer Object and links it o vertices
		void Init(std::vector<Vertex>& vertices);

		void Bind();
		void UnBind();
		void Delete();
	};
}
