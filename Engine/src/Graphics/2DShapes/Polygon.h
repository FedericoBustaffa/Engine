#pragma once

#include <glm/glm.hpp>

#include "Engine.h"

class Polygon
{
public:
	Polygon()
		: model(1.0)
	{
	}

	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }

protected:
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;

	glm::mat4 model;
};

class Square : public Polygon
{
public:
	Square(const glm::vec2& bottom_left, float length)
		: bottom_left(bottom_left), length(length)
	{
		va = std::make_shared<VertexArray>();

		float buffer[4 * 2] = {
			bottom_left.x, bottom_left.y,
			bottom_left.x, bottom_left.y + length,
			bottom_left.x + length, bottom_left.y + length,
			bottom_left.x + length, bottom_left.y
		};
		vb = std::make_shared<Buffer>(sizeof(buffer), buffer);

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};
		ib = std::make_shared<IndexBuffer>(6, indices);
	}

private:
	glm::vec2 bottom_left;
	float length;
};