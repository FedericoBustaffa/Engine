#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Player.h"

class Ball
{
public:
	Ball(const std::vector<glm::vec4>& buffer);

	inline const std::vector<glm::vec4>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }
	inline const glm::mat4& GetModel() const { return model; }
	inline float GetXSpeed() const { return x_speed; }
	inline float GetYSpeed() const { return y_speed; }
	inline void SetXSpeed(float speed) { x_speed = speed; }
	inline void SetYSpeed(float speed) { y_speed = speed; }

	void Move(const TimeStep& ts);
	bool BoundCollision(double lower_bound, double upper_bound);
	bool PlayerCollision(const std::shared_ptr<Player>& player);
	bool Goal(float goal);

private:
	std::vector<glm::vec4> vertices;

	// rendering objects
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;

	// stats
	float x_speed = 0.0f;
	float y_speed = 0.0f;
	glm::vec3 move;
	glm::mat4 model;
};