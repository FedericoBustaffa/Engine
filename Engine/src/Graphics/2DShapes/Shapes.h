#pragma once

#include <glm/glm.hpp>

#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"

class Shape
{
protected:
	Shape()
		: model(1.0), color(0.0)
	{
	}

public:
	inline void SetModel(const glm::mat4& new_model) { model = new_model; }
	inline const glm::mat4& GetModel() const { return model; }
	
	void SetColor(float red, float green, float blue, float alpha);
	void SetColor(const glm::vec4& color) { this->color = color; }
	inline const glm::vec4& GetColor() const { return color; }
	
protected:
	glm::mat4 model;
	glm::vec4 color;
};

// poligono generico
class Polygon : public Shape
{
public:
	Polygon(size_t sides, float length);
	Polygon(size_t sides, const std::vector<glm::vec2>& vertices);

	inline const std::vector<glm::vec2>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }

protected:
	size_t sides;
	std::vector<glm::vec2> vertices;
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
};

// triangolo
class Triangle : public Polygon
{
public:
	Triangle(const std::vector<glm::vec2>& vertices);

	inline const glm::vec2& GetV1() const { return v1; }
	inline const glm::vec2& GetV2() const { return v2; }
	inline const glm::vec2& GetV3() const { return v3; }

private:
	glm::vec2 v1, v2, v3;
};

// quadrilatero
class Quad : public Polygon
{
public:
	Quad(const std::vector<glm::vec2>& vertices);
};

// rettangolo
class Rectangle : public Quad
{
public:
	Rectangle(const glm::vec2& bottom_left, const glm::vec2& top_right);

	inline const glm::vec2& GetBottomLeft() const { return bottom_left; }
	inline const glm::vec2& GetTopRight() const { return top_right; }

private:
	glm::vec2 bottom_left, top_right;
};

// quadrato
class Square : public Rectangle
{
public:
	Square(const glm::vec2& bottom_left, float length);

	inline const glm::vec2& GetBottomLeft() const { return bottom_left; }
	inline float GetLength() const { return length; }

private:
	glm::vec2 bottom_left;
	float length;
};

// cerchio
class Circle : public Shape
{
public:
	Circle(const glm::vec2& center, float radius);

	inline const glm::vec2& GetCenter() const { return center; }
	inline float GetRadius() const { return radius; }

private:
	glm::vec2 center;
	float radius;
};