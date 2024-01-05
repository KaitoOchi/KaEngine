#include "KaEnginePreCompile.h"
#include "EBO.h"

namespace nsKaEngine {

	EBO::EBO()
	{

	}

	EBO::~EBO()
	{

	}

	void EBO::Init(std::vector<GLuint>& indices)
	{
		glGenBuffers(1, &ID);
		//Bind he VBO specifying it's a GL_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		// Introduce the verticles into the VBO 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	void EBO::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void EBO::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void EBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}