#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertex_source, const std::string& fragment_source);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
	uint32_t id;
};