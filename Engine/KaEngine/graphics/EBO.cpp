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
		glGenBuffers(1, &m_id);
		//Bind he VBO specifying it's a GL_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		// Introduce the verticles into the VBO 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}
}