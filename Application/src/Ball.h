#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"

class Ball
{
public:
	Ball(const std::vector<glm::vec4>& buffer);

	inline const std::vector<glm::vec4>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }
	inline const glm::mat4& GetModel() const { return model; }

private:
	std::vector<glm::vec4> vertices;

	// rendering objects
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;

	// stats
	float speed;
	glm::vec3 move;
	glm::mat4 model;
};