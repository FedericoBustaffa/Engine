#pragma once

#include "Engine.h"

class Triangle
{
public:
	Triangle(size_t size, void* data, const std::shared_ptr<Layout>& layout);
	const std::shared_ptr<VertexArray>& GetVA() const;

private:
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
};