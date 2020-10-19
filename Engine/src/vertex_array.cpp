#include "vertex_array.h"

#include <GL/glew.h>

struct vertex_attributes
{
	int components;
	long int offset;
};

vertex_array::vertex_array()
	: id(0), index(0), stride(0)
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

vertex_array::~vertex_array()
{
	glDeleteVertexArrays(1, &id);
}

void vertex_array::bind() const
{
	glBindVertexArray(id);
}

void vertex_array::unbind() const
{
	glBindVertexArray(0);
}

void vertex_array::push(int components)
{
	vertex_attributes attr;
	attr.components = components;
	attr.offset = stride;
	stride += components * sizeof(float);
	attribs.push_back(attr);
}

void vertex_array::enable()
{
	for (const auto& i : attribs)
	{
		glVertexAttribPointer(index, i.components, GL_FLOAT, GL_FALSE, stride, (void*)i.offset);
		glEnableVertexAttribArray(index);
		index++;
	}
}

void vertex_array::disable()
{
	for (const auto& i : attribs)
	{
		glDisableVertexAttribArray(index);
		index--;
	}
}