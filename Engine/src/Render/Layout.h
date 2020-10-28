#pragma once

#include <string>
#include <vector>

enum class ShaderType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Double, Double2, Double3, Double4
};

struct BufferElement
{
	std::string name;
	ShaderType type;
	int offset;

	BufferElement(const std::string name, ShaderType type)
		: name(name), type(type), offset(0)
	{
	}
};

class Layout
{
public:
	Layout(const std::vector<BufferElement>& elements);

	int GetStride() const;
	std::vector<BufferElement>::iterator begin() { return elements.begin(); }
	std::vector<BufferElement>::iterator end() { return elements.end(); }

private:
	std::vector<BufferElement> elements;
	int stride;
};
