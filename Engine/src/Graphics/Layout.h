#pragma once

#include <string>
#include <vector>

enum class ShaderType
{
	None = 0,
	Float, Double, Char, Int
};

unsigned int SizeOfShaderType(ShaderType type);
unsigned int ShaderTypeToGLType(ShaderType type);

struct BufferElement
{
	std::string name;
	ShaderType type;
	int count, offset;

	BufferElement(const std::string name, ShaderType type, int count)
		: name(name), type(type), count(count), offset(0)
	{
	}
};

class Layout
{
public:
	Layout(const std::vector<BufferElement>& elements);

	const std::vector<BufferElement>& GetElements() const;
	int GetStride() const;

private:
	std::vector<BufferElement> elements;
	int stride;
};
