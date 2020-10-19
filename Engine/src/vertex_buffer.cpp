#include "vertex_buffer.h"

#include <GL/glew.h>

vertex_buffer::vertex_buffer(float* data, size_t size)
	: id(0)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
}

vertex_buffer::~vertex_buffer()
{
	glDeleteBuffers(1, &id);
}

void vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void vertex_buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}