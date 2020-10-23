#include "VertexArray.h"

#include <GL/glew.h>

struct VertexAttributes
{
	int components;
	long int offset;
};

VertexArray::VertexArray()
	: id(0), index(0), stride(0)
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() const
{
	glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::Push(int components)
{
	VertexAttributes attr;
	attr.components = components;
	attr.offset = stride;
	stride += components * sizeof(float);
	attribs.push_back(attr);
}

void VertexArray::Enable()
{
	for (const auto& i : attribs)
	{
		glVertexAttribPointer(index, i.components, GL_FLOAT, GL_FALSE, stride, &i.offset);
		glEnableVertexAttribArray(index);
		index++;
	}
}

void VertexArray::Disable()
{
	for (const auto& i : attribs)
	{
		glDisableVertexAttribArray(index);
		index--;
	}
}