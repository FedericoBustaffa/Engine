#include "Buffer.h"

#include <GL/glew.h>

Buffer::Buffer(size_t size, void* data)
	: id(0), layout(nullptr)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
	delete layout;
}

void Buffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void Buffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::SetLayout(const Layout& layout)
{
	this->layout = new Layout(layout);
}

const Layout& Buffer::GetLayout() const
{
	return *layout;
}



IndexBuffer::IndexBuffer(int count, unsigned int* data)
	: id(0), count(count)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int IndexBuffer::GetCount() const
{
	return count;
}