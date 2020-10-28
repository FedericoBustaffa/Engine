#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
	: id(0)
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

void VertexArray::EnableLayout(const Buffer& buffer)
{
	const std::vector<BufferElement>& elements = buffer.GetLayout().GetElements();

	int index = 0;
	for (const auto& i : elements)
	{
		glVertexAttribPointer(
			index,
			i.count,
			ShaderTypeToGLType(i.type),
			GL_FALSE,
			buffer.GetLayout().GetStride(),
			(void*)i.offset
		);
		glEnableVertexAttribArray(index);
		index++;
	}
}
