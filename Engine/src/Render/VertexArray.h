#pragma once

#include <vector>

struct VertexAttributes;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void Push(int components);
	void Enable();
	void Disable();

private:
	unsigned int id, index, stride;
	std::vector<VertexAttributes> attribs;
};