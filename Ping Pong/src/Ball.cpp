#include "Ball.h"

#include <glm/gtc/matrix_transform.hpp>

Ball::Ball(const glm::vec2& center, float radius)
	: move(0.0)
{
	shape = std::make_shared<Circle>(center, radius);
}

void Ball::SetSpeed(float speed)
{
	this->speed = speed;
	x_speed = speed * glm::cos(glm::radians(direction));
	y_speed = speed * glm::sin(glm::radians(direction));
}

void Ball::SetDirection(float direction)
{
	this->direction = direction;
	x_speed = speed * glm::cos(glm::radians(direction));
	y_speed = speed * glm::sin(glm::radians(direction));
}

void Ball::Move(float ts)
{
	move.x += x_speed * ts;
	move.y += y_speed * ts;

	shape->SetModel(glm::translate(glm::mat4(1.0), move));
}

void Ball::BoundCollision(double lower_bound, double upper_bound)
{
	glm::vec4 bottom = shape->GetModel() * shape->GetBottom();
	glm::vec4 top = shape->GetModel() * shape->GetTop();

	if (bottom.y <= lower_bound || top.y >= upper_bound)
		SetDirection(360.0f - direction);
}

void Ball::PlayerCollision(const std::shared_ptr<Player>& player)
{
	glm::vec4 p_bottom_left = player->GetModel() * player->GetShape()->GetBottomLeft();
	glm::vec4 p_top_right = player->GetModel() * player->GetShape()->GetTopRight();

	if (p_bottom_left.x < 0)
	{
		glm::vec4 left = shape->GetModel() * shape->GetLeft();
		if (left.x <= p_top_right.x && left.x >= p_top_right.x - 0.1f)
		{
			if (left.y <= p_top_right.y && left.y >= p_bottom_left.y)
				SetDirection(180.0f - direction);
		}
	}
	else
	{
		glm::vec4 right = shape->GetModel() * shape->GetRight();
		if (right.x >= p_bottom_left.x && right.x <= p_bottom_left.x + 0.1f)
		{
			if (right.y <= p_top_right.y && right.y >= p_bottom_left.y)
				SetDirection(180.0f - direction);
		}
	}
}

bool Ball::Goal(float goal)
{
	glm::vec4 left = shape->GetModel() * shape->GetLeft();
	glm::vec4 right = shape->GetModel() * shape->GetRight();

	if (goal < 0 && left.x < goal)
	{
		shape->SetModel(glm::mat4(1.0));
		move = glm::vec3(0.0);
		SetSpeed(0);
		return true;
	}
	else if (goal > 0 && right.x > goal)
	{
		shape->SetModel(glm::mat4(1.0));
		move = glm::vec3(0.0);
		SetSpeed(0);
		return true;
	}

	return false;
}
