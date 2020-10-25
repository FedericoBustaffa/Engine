#include "Shader.h"

#include <iostream>
#include <GL/glew.h>

static unsigned int CompileShader(unsigned int type, const std::string& source);

Shader::Shader(const std::string& vertex_source, const std::string& fragment_source)
	: id(0)
{
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_source);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_source);

	id = glCreateProgram();
	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glDetachShader(id, vs);
	glDetachShader(id, fs);
	glValidateProgram(id);
	glUseProgram(id);

	glDeleteShader(vs);
	glDeleteShader(fs);
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


// utility
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader_id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader_id, 1, &src, nullptr);
	glCompileShader(shader_id);

	int success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(shader_id, length, &length, message);

		if (type == GL_VERTEX_SHADER)
			std::cout << "VERTEX::" << std::flush;
		else if (type == GL_FRAGMENT_SHADER)
			std::cout << "FRAGMENT::" << std::flush;
		std::cout << "SHADER compile error: " << message << std::endl;

		delete[] message;
		glDeleteShader(shader_id);
		return -1;
	}

	return shader_id;
}