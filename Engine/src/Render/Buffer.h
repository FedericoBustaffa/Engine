#pragma once

class Buffer
{
public:
	Buffer(size_t size, void* data);
	~Buffer();

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


class BufferLayout
{
public:

private:

};
