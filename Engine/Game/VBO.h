#pragma once

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// generates a Vertex Buffer Object and links it o vertices
	VBO(GLfloat* verices, GLsizeiptr size);

	void Bind();
	void UnBind();
	void Delete();
};