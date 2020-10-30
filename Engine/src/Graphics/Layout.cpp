#include "Layout.h"

#include <GL/glew.h>

unsigned int SizeOfShaderType(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float:		return 4;
	case ShaderType::Float2:	return 4 * 2;
	case ShaderType::Float3:	return 4 * 3;
	case ShaderType::Float4:	return 4 * 4;
	
	case ShaderType::Double:	return 8;
	case ShaderType::Double2:	return 8 * 2;
	case ShaderType::Double3:	return 8 * 3;
	case ShaderType::Double4:	return 8 * 4;
	}

	return 0;
}

int ShaderTypeCount(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float:		return 1;
	case ShaderType::Float2:	return 2;
	case ShaderType::Float3:	return 3;
	case ShaderType::Float4:	return 4;
	
	case ShaderType::Double:	return 1;
	case ShaderType::Double2:	return 2;
	case ShaderType::Double3:	return 3;
	case ShaderType::Double4:	return 4;
	}

	return 0;
}

unsigned int ShaderTypeToGLType(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float:		return GL_FLOAT;
	case ShaderType::Float2:	return GL_FLOAT;
	case ShaderType::Float3:	return GL_FLOAT;
	case ShaderType::Float4:	return GL_FLOAT;
	
	case ShaderType::Double:	return GL_DOUBLE;
	case ShaderType::Double2:	return GL_DOUBLE;
	case ShaderType::Double3:	return GL_DOUBLE;
	case ShaderType::Double4:	return GL_DOUBLE;
	}

	return -1;
}

Layout::Layout(const std::vector<BufferElement>& elements)
	: elements(elements), stride(0)
{
	for (auto& elem : this->elements)
	{
		elem.offset += stride;
		stride += SizeOfShaderType(elem.type);
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
