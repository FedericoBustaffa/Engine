#include "Ball.h"

#include <glm/gtc/matrix_transform.hpp>

Ball::Ball(const std::vector<glm::vec4>& buffer)
	: vertices(buffer), move(0.0), model(1.0)
{
	// layout
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 4 }
	}));

	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(buffer.size() * sizeof(glm::vec4), (void*)buffer.data());

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	ib = std::make_shared<IndexBuffer>(6, indices);

	vb->SetLayout(layout);
	va->AddBuffer(vb);
	va->SetIndexBuffer(ib);
}

void Ball::Move(const TimeStep& ts)
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

bool Ball::PlayerCollision(const std::shared_ptr<Player>& player, const TimeStep& ts)
{
	glm::vec4 bottom_left = model * vertices[0];
	glm::vec4 top_right = model * vertices[2];

	glm::vec4 p_bottom_left = player->GetModel() * player->GetVertices()[0];
	glm::vec4 p_top_right = player->GetModel() * player->GetVertices()[2];
	
	if (p_top_right.x < 0)
	{
		if (bottom_left.x < p_top_right.x)
		{
			if ((bottom_left.y < p_top_right.y && bottom_left.y > p_bottom_left.y)
				|| (top_right.y < p_top_right.y && top_right.y > p_bottom_left.y))
			{
				x_speed *= -1;
				return true;
			}
		}
	}
	else
	{
		if (top_right.x > p_bottom_left.x)
		{
			if ((bottom_left.y < p_top_right.y && bottom_left.y > p_bottom_left.y)
				|| (top_right.y < p_top_right.y && top_right.y > p_bottom_left.y))
			{
				x_speed *= -1;
				return true;
			}
		}
	}

	return false;
}
