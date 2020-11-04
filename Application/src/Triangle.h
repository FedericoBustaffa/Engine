#pragma once

#include <glm/glm.hpp>

#include "Engine.h"

class Triangle
{
public:
	Triangle(size_t size, void* data, const std::shared_ptr<Layout>& layout);
	const std::shared_ptr<VertexArray>& GetVA() const;
	void SetModel(const glm::mat4& model);
	const glm::mat4& GetModel() const;

private:
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;

	glm::mat4 model;
};