#include "Shader.h"

#include <GL/glew.h>

Shader::Shader(const std::string& filepath)
	: id(0)
{

}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::Bind() const
{
	glUseProgram(id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}