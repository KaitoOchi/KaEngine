#pragma once

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void UnBind();
	void Delete();
};