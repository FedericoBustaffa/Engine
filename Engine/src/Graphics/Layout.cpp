#include "Layout.h"

#include <GL/glew.h>

unsigned int SizeOfShaderType(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float:		return 4;
	case ShaderType::Double:	return 8;
	case ShaderType::Char:		return 1;
	case ShaderType::Int:		return 4;
	}

	return 0;
}

unsigned int ShaderTypeToGLType(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float:		return GL_FLOAT;
	case ShaderType::Double:	return GL_DOUBLE;
	case ShaderType::Char:		return GL_BYTE;
	case ShaderType::Int:		return GL_INT;
	}

	return -1;
}

Layout::Layout(const std::vector<BufferElement>& elements)
	: elements(elements), stride(0)
{
	for (auto& elem : this->elements)
	{
		elem.offset += stride;
		stride += elem.count * SizeOfShaderType(elem.type);
	}
}

const std::vector<BufferElement>& Layout::GetElements() const
{
	return elements;
}

int Layout::GetStride() const
{
	return stride;
}
