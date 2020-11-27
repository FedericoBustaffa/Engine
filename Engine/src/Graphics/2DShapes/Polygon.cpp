#include "Shapes.h"

void Shape::SetColor(float red, float green, float blue, float alpha)
{
	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = alpha;
}

static glm::vec3 gen(size_t n, size_t step, size_t lim)
{
	if (n + step * 2 >= lim) { return { n, n + step, 0 }; }
	return { n, n + step, n + (step * 2) };
}

Polygon::Polygon(size_t sides, float length)
	: Shape(), sides(sides)
{
	va = std::make_shared<VertexArray>();

	float angle = 0.0f;
	float angle_step = 360.0f / sides;
	float radius = length / 2 * glm::sin(glm::radians(angle_step));
	float x, y;
	for (int i = 0; i < sides; i++)
	{
		x = radius * glm::cos(glm::radians(angle));
		y = radius * glm::sin(glm::radians(angle));
		vertices.push_back({ x, y , 0.0, 1.0 });
		angle += angle_step;
	}

	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec4), (void*)vertices.data());
	this->vertices = vertices;
	
	std::vector<unsigned int> indices;
	size_t count = 0;
	size_t step = 1;
	while (count < sides - 2)
	{
		for (size_t i = 0; i < sides - step; i += step * 2)
		{
			glm::vec3 triple = gen(i, step, sides);
			indices.push_back((unsigned int)triple.x);
			indices.push_back((unsigned int)triple.y);
			indices.push_back((unsigned int)triple.z);
			count++;
		}
		step *= 2;
	}
	ib = std::make_shared<IndexBuffer>(indices);

	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 4 }
		}));

	vb->SetLayout(layout);
	va->SetBuffer(vb);
	va->SetIndexBuffer(ib);
}

Polygon::Polygon(size_t sides, const std::vector<glm::vec2>& vertices_)
	: Shape(), sides(sides)
{
	if (vertices_.size() != sides)
		return;

	for (const auto& vertex2D : vertices_)
		vertices.push_back({ vertex2D.x, vertex2D.y, 0.0, 1.0 });

	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec4), (void*)vertices.data());
	
	std::vector<unsigned int> indices;
	size_t count = 0;
	size_t step = 1;
	while (count < sides - 2)
	{
		for (size_t i = 0; i < sides - step; i += step * 2)
		{
			glm::vec3 triple = gen(i, step, sides);
			indices.push_back((unsigned int)triple.x);
			indices.push_back((unsigned int)triple.y);
			indices.push_back((unsigned int)triple.z);
			count++;
		}
		step *= 2;
	}

	ib = std::make_shared<IndexBuffer>(indices);

	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 4 }
	}));
	
	vb->SetLayout(layout);
	va->SetBuffer(vb);
	va->SetIndexBuffer(ib);
}
