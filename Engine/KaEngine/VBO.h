#pragma once

namespace nsKaEngine {

	class VBO
	{
	public:
		// Reference ID of the Vertex Buffer Object
		GLuint ID;

		VBO();
		~VBO();

		// generates a Vertex Buffer Object and links it o vertices
		void Init(GLfloat* verices, GLsizeiptr size);

		void Bind();
		void UnBind();
		void Delete();
	};
}
