#include "KaEnginePreCompile.h"
#include "VBO.h"

namespace nsKaEngine {

	VBO::VBO()
	{

	}

	VBO::~VBO()
	{

	}

	void VBO::Init(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &m_id);
		//Bind he VBO specifying it's a GL_ARRAY_BUFFER
		Bind();
		// Introduce the verticles into the VBO 
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}
}