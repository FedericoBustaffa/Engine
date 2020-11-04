#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"

class Triangle
{
public:
	Triangle(size_t size, void* buffer);

	const std::shared_ptr<VertexArray>& GetVA() const;
	void SetLayout(const std::shared_ptr<Layout>& layout);

private:
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
};