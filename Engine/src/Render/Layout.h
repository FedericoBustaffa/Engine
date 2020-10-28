#pragma once

#include <string>
#include <vector>

enum class ShaderType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Double, Double2, Double3, Double4
};

unsigned int SizeOfShaderType(ShaderType type);
int ShaderTypeCount(ShaderType type);
unsigned int ShaderTypeToGLType(ShaderType type);

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

	const std::vector<BufferElement>& GetElements() const;
	int GetStride() const;

private:
	std::vector<BufferElement> elements;
	int stride;
};
