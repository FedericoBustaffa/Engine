#pragma once

class VertexBuffer
{
public:
	VertexBuffer(size_t size, void* data);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int id;
};



class IndexBuffer
{
public:
	IndexBuffer(size_t count, unsigned int* data);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int id;
};