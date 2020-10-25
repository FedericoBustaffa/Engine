#pragma once

#include <string>
#include <vector>

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


enum class ShaderType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Double, Double2, Double3, Double4,
	Int, Int2, Int3, Int4
};

struct BufferElements
{
	std::string name;
	ShaderType type;

	BufferElements(const std::string& name, ShaderType type)
		: name(name), type(type)
	{
	}
};

class BufferLayout
{
public:
	BufferLayout(const std::vector<BufferElements>& elements);

private:
	std::vector<BufferElements> elements;
};
