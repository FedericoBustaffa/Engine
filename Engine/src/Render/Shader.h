#pragma once

#include <string>

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int id;
};