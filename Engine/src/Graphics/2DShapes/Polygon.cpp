#include "Shapes.h"

glm::vec3 gen(size_t n, size_t step, size_t lim)
{
	if (n + step * 2 >= lim) { return { n, n + step, 0 }; }
	return { n, n + step, n + (step * 2) };
}

Polygon::Polygon(size_t sides, float length)
	: sides(sides), model(1.0), color(0.0)
{
	va = std::make_shared<VertexArray>();

	std::vector<glm::vec2> vertices;
	float angle = 0.0f;
	float angle_step = 360.0f / sides;
	float radius = length / 2 * glm::sin(glm::radians(angle_step));
	float x, y;
	for (int i = 0; i < sides; i++)
	{
		x = radius * glm::cos(glm::radians(angle));
		y = radius * glm::sin(glm::radians(angle));
		vertices.push_back({ x, y });
		angle += angle_step;
	}

	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec2), (void*)vertices.data());
	
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
		{ "position", ShaderType::Float, 2 }
		}));

	vb->SetLayout(layout);
	va->SetBuffer(vb);
	va->SetIndexBuffer(ib);
}

Polygon::Polygon(const std::vector<glm::vec2>& vertices)
	: sides(vertices.size()), vertices(vertices), model(1.0), color(0.0)
{
	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec2), (void*)vertices.data());
	
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
		{ "position", ShaderType::Float, 2 }
	}));
	
	vb->SetLayout(layout);
	va->SetBuffer(vb);
	va->SetIndexBuffer(ib);
}

void Polygon::SetColor(float red, float green, float blue, float alpha)
{
	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = alpha;
}