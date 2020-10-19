#pragma once

#include <vector>

struct vertex_attributes;

class vertex_array
{
public:
	vertex_array();
	~vertex_array();

	void bind() const;
	void unbind() const;
	void push(int components);
	void enable();
	void disable();

private:
	unsigned int id, index, stride;
	std::vector<vertex_attributes> attribs;
};