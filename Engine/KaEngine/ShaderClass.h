#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string get_file_contents(const char* fileName);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();

private:
	void compileErrors(unsigned int shader, const char* type);
};