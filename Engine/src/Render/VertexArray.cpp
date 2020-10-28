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
	const std::vector<BufferElement>& elements = buffer.GetLayout().GetElements();

	int index = 0;
	for (const auto& i : elements)
	{
		glVertexAttribPointer(
			index,
			ShaderTypeCount(i.type),
			ShaderTypeToGLType(i.type),
			GL_FALSE,
			buffer.GetLayout().GetStride(),
			(void*)i.offset
		);
		glEnableVertexAttribArray(index);
		index++;
	}
}

void VertexArray::SetIndexBuffer(const IndexBuffer& ib)
{
	index_buffer = new IndexBuffer(ib);
}

int VertexArray::GetIndexCount() const
{
	return index_buffer->GetCount();
}