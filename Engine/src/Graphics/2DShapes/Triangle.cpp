#include "Shapes.h"

Triangle::Triangle(const std::vector<glm::vec2>& vertices)
{
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 2 }
	}));
	
	va = std::make_shared<VertexArray>();

	this->vertices = vertices;
	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec2), (void*)vertices.data());

	unsigned int indices[3] = { 0, 1, 2 };
	ib = std::make_shared<IndexBuffer>(3, indices);

	vb->SetLayout(layout);
	va->AddBuffer(vb);
	va->SetIndexBuffer(ib);
}

Triangle::Triangle(const glm::vec2& vertex, float length)
{
	// triangolo equilatero
/*	va = std::make_shared<VertexArray>();

	vertices[0] = vertex;
	vertices[1].x = vertex.x + length;
	vertices[1].y = vertex.y;
	vertices[2].x = length * cos(glm::radians(60.0f));
	vertices[2].y = length * sin(glm::radians(60.0f));

	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec2), (void*)vertices.data());
	
	unsigned int indices[3] = { 0, 1, 2 };
	ib = std::make_shared<IndexBuffer>(3, indices);

	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 2 }
	}));

	vb->SetLayout(layout);
	va->AddBuffer(vb);
	va->SetIndexBuffer(ib);*/
}