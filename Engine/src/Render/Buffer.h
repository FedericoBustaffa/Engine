#pragma once

#include <string>
#include <vector>

// ShaderType --------------------------------------
enum class ShaderType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Double, Double2, Double3, Double4,
	Int, Int2, Int3, Int4
};


// position, color, normalize ----------------------
struct BufferElement
{
	std::string name;
	ShaderType type;
	unsigned int size, offset;

	BufferElement(const std::string& name, ShaderType type);
};


// BufferLayout ----------------------------------
class BufferLayout
{
public:
	BufferLayout(const std::vector<BufferElement>& elements);

	const std::vector<BufferElement>& GetElements() const;
	unsigned int GetStride() const;
	
	std::vector<BufferElement>::iterator Begin();
	std::vector<BufferElement>::iterator End();

private:
	std::vector<BufferElement> elements;
	unsigned int stride;
};


// Buffer -------------------------------------------
class Buffer
{
public:
	Buffer(size_t size, void* data);
	~Buffer();

	void Bind() const;
	void Unbind() const;
	const BufferLayout& GetLayout() const { return layout; }
	void SetLayout(const BufferLayout& layout) { this->layout = layout; }

private:
	unsigned int id;
	BufferLayout layout;
};


// IndexBuffer ---------------------------------------
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

