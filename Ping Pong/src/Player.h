#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"

class Player
{
public:
	Player(const std::string& name, const glm::vec2& bottom_left, const glm::vec2& top_right);

	inline const std::shared_ptr<Rectangle>& GetShape() const { return shape; }
	inline const glm::mat4& GetModel() const { return shape->GetModel(); }

	inline const std::string& GetName() const { return name; }
	inline int GetPoints() const { return points; }
	inline void IncPoints() { points++; }
	
	/*void MoveUp(const TimeStep& ts);
	void MoveDown(const TimeStep& ts);
	bool UpperBoundCollision(double upper_bound);
	bool LowerBoundCollision(double lower_bound);*/

private:
	// values
	std::string name;
	int points = 0;

	// shape
	std::shared_ptr<Rectangle> shape;

	// stats
	float speed = 10.0f;
	glm::vec3 move;
};