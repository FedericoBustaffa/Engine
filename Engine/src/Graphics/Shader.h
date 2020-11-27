#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertex_source, const std::string& fragment_source);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniform4f(const std::string& name, const glm::vec4& color);
	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
	int GetUniformLocation(const std::string& name);

private:
	uint32_t id;
	std::unordered_map<std::string, int> uniform_cache;
};