#pragma once
#include <stb/stb_image.h>

#include "ShaderClass.h"


class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture();
	~Texture();

	void Init(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void TexUnit(Shader* shader, const char* uniform, GLuint unit);
	void Bind();
	void UnBind();
	void Delete();
};