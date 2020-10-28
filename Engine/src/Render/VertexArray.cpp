#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
	: id(0), index_buffer(nullptr)
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

void VertexArray::AddBuffer(const Buffer& buffer)
{
	buffers.push_back(buffer);
}

void VertexArray::SetIndexBuffer(const IndexBuffer& ib)
{
	index_buffer = new IndexBuffer(ib);
}
