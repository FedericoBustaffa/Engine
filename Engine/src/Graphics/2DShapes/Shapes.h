#pragma once

#include <glm/glm.hpp>

#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"

class Polygon
{
public:
	Polygon(size_t sides, float length);
	Polygon(const std::vector<glm::vec2>& vertices);

	inline const std::vector<glm::vec2>& GetVertices() const { return vertices; }
	inline const std::shared_ptr<VertexArray>& GetVA() const { return va; }
	inline const glm::mat4& GetModel() const { return model; }
	void SetColor(float red, float green, float blue, float alpha);
	void SetColor(const glm::vec4& color) { this->color = color; }
	inline const glm::vec4& GetColor() const { return color; }

protected:
	size_t sides;
	std::vector<glm::vec2> vertices;
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
	glm::mat4 model;
	glm::vec4 color;
};
