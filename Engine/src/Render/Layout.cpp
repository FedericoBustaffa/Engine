#include "Layout.h"

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

Layout::Layout(const std::vector<BufferElement>& elements)
	: elements(elements), stride(0)
{
	for (auto& elem : this->elements)
	{
		elem.offset += stride;
		stride += SizeOfShaderType(elem.type);
	}
}

int Layout::GetStride() const
{
	return stride;
}
