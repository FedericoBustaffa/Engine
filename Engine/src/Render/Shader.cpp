#include "Shader.h"

#include <iostream>
#include <GL/glew.h>

static void CompileShader(const std::string& source)
{
	
}

Shader::Shader(const std::string& vertex_source, const std::string& fragment_source)
	: id(0)
{
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vertex_source.c_str(), nullptr);
	glCompileShader(vs);
	int success;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetShaderInfoLog(vs, 512, nullptr, info_log);
		std::cout << "shader error: " << info_log << std::endl;
		glDeleteShader(vs);
	}
	
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fragment_source.c_str(), nullptr);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetShaderInfoLog(fs, 512, nullptr, info_log);
		std::cout << "shader error: " << info_log << std::endl;
		glDeleteShader(fs);
	}


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