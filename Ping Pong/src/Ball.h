#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Player.h"

class Ball
{
public:
	Ball(const glm::vec2& center, float radius);

	inline const std::shared_ptr<Circle>& GetShape() const { return shape; }
	inline const glm::mat4& GetModel() const { return shape->GetModel(); }
	inline const glm::vec4& GetCenter() const { return shape->GetCenter(); }

	inline float GetSpeed() const { return speed; }
	void SetSpeed(float speed);
	inline float GetDirection() const { return direction; }
	void SetDirection(float direction);

	void Move(float ts);
	void BoundCollision(double lower_bound, double upper_bound);
	void PlayerCollision(const std::shared_ptr<Player>& player);
	bool Goal(float goal);

private:
	// shape
	std::shared_ptr<Circle> shape;

	// stats
	float speed = 0.0f;
	float x_speed = 0.0f;
	float y_speed = 0.0f;
	float direction = 0.0f;
	glm::vec3 move;
};