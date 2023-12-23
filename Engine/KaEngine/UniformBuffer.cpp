#include "KaEnginePreCompile.h"
#include "UniformBuffer.h"

namespace nsKaEngine {

	UniformBuffer::UniformBuffer()
	{

	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &ubo);
	}

	void UniformBuffer::Init(void* data, const int size)
	{
		//UniformBufferÇçÏê¨ÅB
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, size, &data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::Update(const int index)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, ubo);
	}
}