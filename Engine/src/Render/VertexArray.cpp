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
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
{
	glBindVertexArray(id);
	ib->Bind();

	index_buffer = ib;
}

void VertexArray::AddBuffer(const std::shared_ptr<Buffer>& buffer)
{
	const auto& elements = buffer->GetLayout()->GetElements();
	glBindVertexArray(id);
	buffer->Bind();
	
	int index = 0;
	for (const auto& i : elements)
	{
		glVertexAttribPointer(
			index,
			i.count,
			ShaderTypeToGLType(i.type),
			GL_FALSE,
			buffer->GetLayout()->GetStride(),
			(void*)i.offset
		);
		glEnableVertexAttribArray(index);
		index++;
	}

	buffers.push_back(buffer);
}

int VertexArray::GetIndexCount() const
{
	return index_buffer->GetCount();
}