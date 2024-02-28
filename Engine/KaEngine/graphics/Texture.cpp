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

		// Texture
		int widthImg, heightImg, numColCh;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

		glGenTextures(1, &m_id);
		Bind(slot);

		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(m_target, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
		glGenerateMipmap(m_target);

		stbi_image_free(bytes);
		UnBind();
	}

	void Texture::TexUnit(
		const Shader* shader,
		const char* uniform,
		const GLuint slot
	) {
		GLuint texUni = glGetUniformLocation(shader->GetShaderID(), uniform);
		glUniform1i(texUni, slot);
	}
}