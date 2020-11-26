#pragma once

#include <glm/glm.hpp>

#include "Engine.h"

class Polygon
{
public:
	Polygon();

	inline const std::vector<glm::vec2>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }
	inline const glm::mat4& GetModel() const { return model; }
	void SetColor(float red, float green, float blue, float alpha);
	void SetColor(const glm::vec4& color) { this->color = color; }
	inline const glm::vec4& GetColor() const { return color; }

protected:
	std::vector<glm::vec2> vertices;
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
	glm::mat4 model;
	glm::vec4 color;
};

class Triangle : public Polygon
{
public:
	Triangle(const std::vector<glm::vec2>& vertices);
	Triangle(const glm::vec2& vertex, float length);
};

/*class Rectangle : public Polygon
{
public:
	Rectangle(const glm::vec2& bottom_left, float width, float height);
	Rectangle(const glm::vec2& bottom_left, const glm::vec2& top_right);

	inline const glm::vec2& GetBottomLeft() const { return bottom_left; }
	inline const glm::vec2& GetTopRight() const { return top_right; }

private:
	glm::vec2 bottom_left;
	glm::vec2 top_right;
	float length;
};*/

class Square : public Polygon
{
public:
	Square(const glm::vec2& bottom_left, float length);
};
