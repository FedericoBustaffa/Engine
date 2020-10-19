#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class shader
{
public:
	shader(const char* vertex_source, const char* fragment_source);
	shader(const std::string& filepath);
	~shader();

	void bind() const;
	void unbind() const;
	void set_uniform4f(const std::string& name, float v1, float v2, float v3);
	void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix);

private:
	int get_uniform_location(const std::string& name);

private:
	unsigned int id;
	std::unordered_map<std::string, int> uniform_cache;
};