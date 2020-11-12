#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(const std::string& name, const std::vector<glm::vec4>& buffer)
	: name(name), vertices(buffer), move(0.0), model(1.0)
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

void Player::MoveUp(const TimeStep& ts)
{
	move.y += speed * ts();
	model = glm::translate(glm::mat4(1.0), move);
}

void Player::MoveDown(const TimeStep& ts)
{
	move.y -= speed * ts();
	model = glm::translate(glm::mat4(1.0), move);
}

bool Player::UpperBoundCollision(double upper_bound)
{
	glm::vec4 top_right = model * vertices[2];
	return top_right.y > upper_bound;
}

bool Player::LowerBoundCollision(double lower_bound)
{
	glm::vec4 top_right = model * vertices[0];
	return top_right.y < lower_bound;
}
