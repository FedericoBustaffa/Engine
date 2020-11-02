#include "Shader.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

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

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location == -1)
		std::cout << "Location of " << name << " does not exist" << std::endl;

	glUniform4f(location, v1, v2, v3, v4);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location == -1)
		std::cout << "Location of " << name << " does not exist" << std::endl;

	glUniformMatrix4fv(location, 1, GL_TRUE, glm::value_ptr(matrix));
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