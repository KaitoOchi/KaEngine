#include "KaEnginePreCompile.h"
#include "UniformBuffer.h"

namespace nsKaEngine {

	UniformBuffer::UniformBuffer()
	{

	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &m_ubo);
	}

	void UniformBuffer::Init(
		const int size,
		GLuint shaderID,
		const char* blockName
	) {

		if (blockName != "ModelUB" &&
			blockName != "SpriteUB"
		) {

			GLuint* uboPtr = KaEngine::GetInstance()->GetUniformBufferBank(blockName);
			if (uboPtr == nullptr) {
				//UniformBufferを作成。
				glGenBuffers(1, &m_ubo);
				glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
				glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
				uboPtr = new GLuint;
				*uboPtr = m_ubo;
				KaEngine::GetInstance()->RegistUniformBufferBank(blockName, uboPtr);
			}
			else {
				m_ubo = *uboPtr;
			}
		}
		else {
			//UniformBufferを作成。
			glGenBuffers(1, &m_ubo);
			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
		}

		//UBOをシェーダーと紐付ける。
		m_blockIndex = glGetUniformBlockIndex(shaderID, blockName);
		glUniformBlockBinding(shaderID, m_blockIndex, m_blockIndex);

		glBindBufferBase(GL_UNIFORM_BUFFER, m_blockIndex, m_ubo);
	}

	void UniformBuffer::Update(void* data, const int size)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, m_blockIndex, m_ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		//データを送信。
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}