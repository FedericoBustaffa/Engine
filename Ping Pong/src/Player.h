#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"

class Player
{
public:
	Player(const std::string& name, const std::vector<glm::vec4>& buffer);

	inline const std::string& GetName() const { return name; }
	inline int GetPoints() const { return points; }
	inline void IncPoints() { points++; }

	inline const std::vector<glm::vec4>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }
	inline const glm::mat4& GetModel() const { return model; }
	
	void MoveUp(const TimeStep& ts);
	void MoveDown(const TimeStep& ts);
	bool UpperBoundCollision(double upper_bound);
	bool LowerBoundCollision(double lower_bound);

private:
	std::string name;
	int points = 0;

	// rendering objects
	std::vector<glm::vec4> vertices;
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;

	// stats
	float speed = 10.0f;
	glm::vec3 move;
	glm::mat4 model;
};