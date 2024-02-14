#include "KaEnginePreCompile.h"
#include "Texture.h"

namespace nsKaEngine {

	Texture::Texture()
	{

	}

	Texture::~Texture()
	{

	}

	void Texture::Init(
		const char* image,
		const GLenum texType,
		const GLuint slot,
		const GLenum format,
		const GLenum pixelType
	) {
		m_target = texType;
		m_slot = slot;

		GLuint* imagePtr = KaEngine::GetInstance()->GetTextureBank(image);
		if (imagePtr == nullptr) {

			// Texture
			int widthImg, heightImg, numColCh;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

			glGenTextures(1, &m_id);
			Bind();

			// Configures the type of algorithm that is used to make the image smaller or bigger
			glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			// Configures the way the texture repeats (if it does at all)
			glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexImage2D(m_target, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
			glGenerateMipmap(m_target);

			stbi_image_free(bytes);
			UnBind();

			imagePtr = new GLuint;
			*imagePtr = m_id;
			KaEngine::GetInstance()->RegistTextureBank(image, imagePtr);
		}
		else {
			m_id = *imagePtr;
		}
	}

	void Texture::TexUnit(
		Shader* shader,
		const char* uniform
	) {
		GLuint texUni = glGetUniformLocation(shader->GetShaderID(), uniform);
		shader->Activate();
		glUniform1i(texUni, m_slot);
	}
}