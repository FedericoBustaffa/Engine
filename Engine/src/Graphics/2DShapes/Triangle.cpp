#include "Shapes.h"

Triangle::Triangle(const std::vector<glm::vec2>& vertices)
	: Polygon(vertices)
{
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 2 }
	}));
	
	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec2), (void*)vertices.data());

	unsigned int indices[3] = { 0, 1, 2 };
	ib = std::make_shared<IndexBuffer>(3, indices);

	vb->SetLayout(layout);
	va->SetBuffer(vb);
	va->SetIndexBuffer(ib);
}