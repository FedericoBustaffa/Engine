#include "Buffer.h"

unsigned int ShaderTypeSize(ShaderType type)
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

	case ShaderType::Int:		return 4;
	case ShaderType::Int2:		return 4 * 2;
	case ShaderType::Int3:		return 4 * 3;
	case ShaderType::Int4:		return 4 * 4;
	}

	return 0;
}


// elements position, color, normal ...
BufferElement::BufferElement(const std::string& name, ShaderType type)
	: name(name), type(type), size(ShaderTypeSize(type)), offset(0)
{
}

unsigned int BufferElement::GetCount() const
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

	case ShaderType::Int:		return 1;
	case ShaderType::Int2:		return 2;
	case ShaderType::Int3:		return 3;
	case ShaderType::Int4:		return 4;
	}

	return 0;
}


// BufferLayout ----------------------------------------
BufferLayout::BufferLayout(const std::vector<BufferElement>& elements)
	: elements(elements), stride(0)
{
	int offset = 0;
	for (auto& elem : this->elements)
	{
		elem.offset = offset;
		offset += elem.size;
		stride += elem.size;
	}
}

const std::vector<BufferElement>& BufferLayout::GetElements() const
{
	return elements;
}

unsigned int BufferLayout::GetStride() const
{
	return stride;
}

std::vector<BufferElement>::iterator BufferLayout::Begin()
{
	return elements.begin();
}

std::vector<BufferElement>::iterator BufferLayout::End()
{
	return elements.end();
}