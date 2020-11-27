#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(const std::string& name, const glm::vec2& bottom_left, const glm::vec2& top_right)
	: name(name), move(0.0)
{
	shape = std::make_shared<Rectangle>(bottom_left, top_right);
}

void Player::MoveUp(const TimeStep& ts)
{
	move.y += speed * ts();
	shape->SetModel(glm::translate(glm::mat4(1.0), move));
}

void Player::MoveDown(const TimeStep& ts)
{
	move.y -= speed * ts();
	shape->SetModel(glm::translate(glm::mat4(1.0), move));
}

bool Player::UpperBoundCollision(double upper_bound)
{
	glm::vec4 top_right = shape->GetModel() * shape->GetTopRight();
	return top_right.y > upper_bound;
}

bool Player::LowerBoundCollision(double lower_bound)
{
	glm::vec4 bottom_left = shape->GetModel() * shape->GetBottomLeft();
	return bottom_left.y < lower_bound;
}
