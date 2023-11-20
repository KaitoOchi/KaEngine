#include "KaEnginePreCompile.h"
#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttribute(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.UnBind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}