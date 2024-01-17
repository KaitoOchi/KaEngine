#include "KaEnginePreCompile.h"
#include "VAO.h"

namespace nsKaEngine {

	VAO::VAO()
	{

	}

	VAO::~VAO()
	{

	}

	void VAO::Init()
	{
		glGenVertexArrays(1, &m_id);
	}

	void VAO::LinkAttribute(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
	{
		vbo.Bind();
		// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		vbo.UnBind();
	}
}