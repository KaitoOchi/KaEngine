#pragma once
#include "VBO.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// generates a VAO ID
	VAO();

	void LinkAttribute(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr sride, void* offset);
	void Bind();
	void UnBind();
	void Delete();
};