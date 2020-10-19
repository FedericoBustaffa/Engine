#include "index_buffer.h"

#include <GL/glew.h>

index_buffer::index_buffer(unsigned int* data, unsigned int count)
	: id(0), count(count)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

index_buffer::~index_buffer()
{
	glDeleteBuffers(1, &id);
}

void index_buffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void index_buffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

unsigned int index_buffer::get_count() const
{
	return count;
}