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
	Polygon(size_t sides, const std::vector<glm::vec2>& vertices_);

	inline size_t GetSides() const { return sides; }
	inline const std::vector<glm::vec4>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }

protected:
	size_t sides;
	std::vector<glm::vec4> vertices;
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
};

// triangolo
class Triangle : public Polygon
{
public:
	Triangle(const std::vector<glm::vec2>& vertices);

	inline const glm::vec4& GetV1() const { return v1; }
	inline const glm::vec4& GetV2() const { return v2; }
	inline const glm::vec4& GetV3() const { return v3; }

private:
	glm::vec4 v1, v2, v3;
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

	inline const glm::vec4& GetBottomLeft() const { return bottom_left; }
	inline const glm::vec4& GetTopRight() const { return top_right; }

private:
	glm::vec4 bottom_left, top_right;
};

// quadrato
class Square : public Rectangle
{
public:
	Square(const glm::vec2& bottom_left, float length);

	inline const glm::vec4& GetBottomLeft() const { return bottom_left; }
	inline float GetLength() const { return length; }

private:
	glm::vec4 bottom_left;
	float length;
};

// cerchio
class Circle : public Shape
{
public:
	Circle(const glm::vec2& center, float radius);

	inline const glm::vec4& GetCenter() const { return center; }
	inline float GetRadius() const { return radius; }
	inline const glm::vec4& GetBottom() const { return bottom; }
	inline const glm::vec4& GetTop() const { return top; }
	inline const glm::vec4& GetLeft() const { return left; }
	inline const glm::vec4& GetRight() const { return right; }

private:
	glm::vec4 center;
	float radius;
	glm::vec4 bottom, top, left, right;
};