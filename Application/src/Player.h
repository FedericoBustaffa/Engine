#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"

class Player
{
public:
	Player(const std::vector<glm::vec4>& buffer);

	inline const std::vector<glm::vec4>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }
	inline const glm::mat4& GetModel() const { return model; }
	
	void MoveUp(const TimeStep& ts);
	void MoveDown(const TimeStep& ts);
	bool UpperBoundCollision(double upper_bound);
	bool LowerBoundCollision(double lower_bound);

private:
	std::vector<glm::vec4> vertices;

	// rendering objects
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;

	// stats
	float speed = 10.0f;
	glm::vec3 move;
	glm::mat4 model;
};