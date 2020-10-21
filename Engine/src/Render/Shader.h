#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char* vertex_source, const char* fragment_source);
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	int GetUniformLocation(const std::string& name);

private:
	unsigned int id;
	std::unordered_map<std::string, int> uniform_cache;
};