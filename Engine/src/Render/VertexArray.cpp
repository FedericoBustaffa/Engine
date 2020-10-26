#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
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
	glBindVertexArray(id);

	buffer.Bind();
	uint32_t index = 0;
	const auto& layout = buffer.GetLayout();
	for (const auto& elem : layout)
	{
		glVertexAttribPointer(index,
			elem.GetCount(),
			)
	}

	buffers.push_back(buffer);
}

void VertexArray::AddIndexBuffer(const IndexBuffer& ib)
{
	glBindVertexArray(id);
	index_buffers.push_back(ib);
}
