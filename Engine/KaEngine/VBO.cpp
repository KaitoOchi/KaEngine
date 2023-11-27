#include "KaEnginePreCompile.h"
#include "VBO.h"

namespace nsKaEngine {

	VBO::VBO()
	{

	}

	VBO::~VBO()
	{

	}

	void VBO::Init(GLfloat* vertices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		//Bind he VBO specifying it's a GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		// Introduce the verticles into the VBO 
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void VBO::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VBO::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	void VBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}