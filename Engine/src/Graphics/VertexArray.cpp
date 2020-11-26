#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
	: id(0)
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() const
{
	glBindVertexArray(id);
	index_buffer->Bind();
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetBuffer(const std::shared_ptr<Buffer>& buffer)
{
	const auto& elements = buffer->GetLayout()->GetElements();
	glBindVertexArray(id);
	buffer->Bind();
	
	int index = 0;
	for (const auto& elem : elements)
	{
		glVertexAttribPointer(
			index,
			elem.count,
			ShaderTypeToGLType(elem.type),
			GL_FALSE,
			buffer->GetLayout()->GetStride(),
			(void*)elem.offset
		);
		glEnableVertexAttribArray(index);
		index++;
	}

	this->buffer = buffer;
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
{
	glBindVertexArray(id);
	ib->Bind();

	index_buffer = ib;
}

size_t VertexArray::GetIndexCount() const
{
	return index_buffer->GetCount();
}