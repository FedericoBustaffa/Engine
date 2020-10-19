#pragma once

class vertex_buffer
{
public:
	vertex_buffer(float* data, size_t size);
	~vertex_buffer();

	void bind() const;
	void unbind() const;

private:
	unsigned int id;
};