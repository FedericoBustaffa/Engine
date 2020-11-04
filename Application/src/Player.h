#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"

class Player
{
public:
	Player(const std::vector<glm::vec4>& buffer, const std::vector<unsigned int>& indices);

	inline const std::vector<glm::vec4>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }
	inline const glm::mat4& GetModel() const { return model; }
	
	void MoveRight(const TimeStep& ts);
	void MoveUp(const TimeStep& ts);
	void MoveLeft(const TimeStep& ts);
	void MoveDown(const TimeStep& ts);
	
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