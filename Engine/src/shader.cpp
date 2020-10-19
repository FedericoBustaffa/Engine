#include "shader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <tuple>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void compile_shader(unsigned int& shader, const char* source);
std::pair<std::string, std::string> parse_shader(const std::string& filepath);

shader::shader(const char* vertex_source, const char* fragment_source)
	: id(0)
{
	id = glCreateProgram();
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

	compile_shader(vs, vertex_source);
	compile_shader(fs, fragment_source);

	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glUseProgram(id);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

shader::shader(const std::string& filepath)
	: id(0)
{
	id = glCreateProgram();
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	std::pair<std::string, std::string> source = parse_shader(filepath);

	compile_shader(vs, source.first.c_str());
	compile_shader(fs, source.second.c_str());

	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glUseProgram(id);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

shader::~shader()
{
	glDeleteProgram(id);
}

void shader::bind() const
{
	glUseProgram(id);
}

void shader::unbind() const
{
	glUseProgram(0);
}

int shader::get_uniform_location(const std::string& name)
{
	if (uniform_cache.find(name) != uniform_cache.end())
		return uniform_cache[name];

	int location = glGetUniformLocation(id, name.c_str());
	uniform_cache[name] = location;

	return location;
}

void shader::set_uniform4f(const std::string& name, float v1, float v2, float v3)
{
	int location = get_uniform_location(name);

	glUniform4f(location, v1, v2, v3, 1.0f);
}

void shader::set_uniform_mat4f(const std::string& name, const glm::mat4& matrix)
{
	int location = get_uniform_location(name);
	
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// SubRoutine
void compile_shader(unsigned int& shader, const char* source)
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

std::pair<std::string, std::string> parse_shader(const std::string& filepath)
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
