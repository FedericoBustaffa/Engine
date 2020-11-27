#include "Ball.h"

#include <glm/gtc/matrix_transform.hpp>

Ball::Ball(const glm::vec2& center, float radius)
	: move(0.0)
{
	shape = std::make_shared<Circle>(center, radius);
}

/*void Ball::Move(const TimeStep& ts)
{
	move.x += x_speed * ts();
	move.y += y_speed * ts();

	model = glm::translate(glm::mat4(1.0), move);
}

bool Ball::BoundCollision(double lower_bound, double upper_bound)
{
	glm::vec4 bottom_left = model * vertices[0];
	glm::vec4 top_right = model * vertices[2];

	if (bottom_left.y < lower_bound || top_right.y > upper_bound)
	{
		y_speed *= -1;
		return true;
	}
	
	return false;
}

bool Ball::PlayerCollision(const std::shared_ptr<Player>& player)
{
	glm::vec4 p_bottom_left = player->GetModel() * player->GetVertices()[0];
	glm::vec4 p_top_right = player->GetModel() * player->GetVertices()[2];
	
	if (p_top_right.x < 0)
	{
		// if ball is in left player
		glm::vec4 bottom_left = model * vertices[0];
		glm::vec4 top_left = model * vertices[1];

		if (bottom_left.x < p_top_right.x && bottom_left.x >  p_top_right.x - 0.1f)
		{
			if ((bottom_left.y < p_top_right.y && bottom_left.y > p_bottom_left.y)
				|| (top_left.y < p_top_right.y && top_left.y > p_bottom_left.y))
			{
				x_speed *= -1;
				return true;
			}
		}
	}
	else
	{
		// if ball is in right player
		glm::vec4 bottom_right = model * vertices[3];
		glm::vec4 top_right = model * vertices[2];

		if (top_right.x > p_bottom_left.x && top_right.x < p_bottom_left.x + 0.1f)
		{
			if ((bottom_right.y < p_top_right.y && bottom_right.y > p_bottom_left.y)
				|| (top_right.y < p_top_right.y && top_right.y > p_bottom_left.y))
			{
				x_speed *= -1;
				return true;
			}
		}
	}

	return false;
}

bool Ball::Goal(float goal)
{
	glm::vec4 bottom_left = model * vertices[0];
	glm::vec4 top_right = model * vertices[2];

	if (goal < 0 && bottom_left.x < goal)
	{
		model = glm::mat4(1.0);
		move = glm::vec3(0.0);
		x_speed = 0;
		y_speed = 0;
		return true;
	}
	else if (goal > 0 && top_right.x > goal)
	{
		model = glm::mat4(1.0);
		move = glm::vec3(0.0);
		x_speed = 0;
		y_speed = 0;
		return true;
	}

	return false;
}*/
