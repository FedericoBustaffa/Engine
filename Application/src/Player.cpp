#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(const std::vector<glm::vec4>& buffer, const std::vector<unsigned int>& indices)
	: vertices(buffer), speed(10.0f), move(0.0), model(1.0)
{
	// layout
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 4 }
	}));

	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(buffer.size() * sizeof(glm::vec4), (void*)buffer.data());
	ib = std::make_shared<IndexBuffer>((int)indices.size(), (unsigned int*)indices.data());

	vb->SetLayout(layout);
	va->AddBuffer(vb);
	va->SetIndexBuffer(ib);
}

void Player::MoveRight(const TimeStep& ts)
{
	move.x += speed * ts();
	model = glm::translate(glm::mat4(1.0), move);
}

void Player::MoveUp(const TimeStep& ts)
{
	move.y += speed * ts();
	model = glm::translate(glm::mat4(1.0), move);
}

void Player::MoveLeft(const TimeStep& ts)
{
	move.x -= speed * ts();
	model = glm::translate(glm::mat4(1.0), move);
}

void Player::MoveDown(const TimeStep& ts)
{
	move.y -= speed * ts();
	model = glm::translate(glm::mat4(1.0), move);
}

