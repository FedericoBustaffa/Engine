#pragma once

class VertexBuffer
{
public:
	VertexBuffer(float* data, size_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int id;
};