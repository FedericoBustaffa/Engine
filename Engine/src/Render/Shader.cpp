#include "Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <tuple>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void CompileShader(unsigned int& shader, const char* source);
std::pair<std::string, std::string> ParseShader(const std::string& filepath);

Shader::Shader(const char* vertex_source, const char* fragment_source)
	: id(0)
{
	id = glCreateProgram();
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

	CompileShader(vs, vertex_source);
	CompileShader(fs, fragment_source);

	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glUseProgram(id);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::Shader(const std::string& filepath)
	: id(0)
{
	id = glCreateProgram();
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	std::pair<std::string, std::string> source = ParseShader(filepath);

	CompileShader(vs, source.first.c_str());
	CompileShader(fs, source.second.c_str());

	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
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

int Shader::GetUniformLocation(const std::string& name)
{
	if (uniform_cache.find(name) != uniform_cache.end())
		return uniform_cache[name];

	int location = glGetUniformLocation(id, name.c_str());
	uniform_cache[name] = location;

	return location;
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3)
{
	int location = GetUniformLocation(name);

	glUniform4f(location, v1, v2, v3, 1.0f);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	int location = GetUniformLocation(name);
	
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// SubRoutine
void CompileShader(unsigned int& shader, const char* source)
{
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	char info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, info_log);
		std::cout << "vertex shader error: " << info_log << std::endl;
	}
}

std::pair<std::string, std::string> ParseShader(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::string line;
	std::stringstream source[2];
	int index = 0;

	while (std::getline(file, line))
	{
		if (line == "#vertex")
			index = 0;
		else if (line == "#fragment")
			index = 1;
		else
			source[index] << line << "\n";
	}

	return std::pair<std::string, std::string>(source[0].str(), source[1].str());
}
