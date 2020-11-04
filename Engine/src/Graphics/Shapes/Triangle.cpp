#include "Triangle.h"

Triangle::Triangle(size_t size, void* buffer)
{
	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(size, buffer);

	uint32_t indices[3] = { 0, 1, 2 };
	ib = std::make_shared<IndexBuffer>(3, indices);
}