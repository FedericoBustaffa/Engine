#include "Shapes.h"

Square::Square(const glm::vec2& bottom_left, float length)
	: Polygon(4)
{
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 2 }
	}));

	va = std::make_shared<VertexArray>();

	vertices = {
		{ bottom_left.x, bottom_left.y},
		{ bottom_left.x, bottom_left.y + length },
		{ bottom_left.x + length, bottom_left.y + length },
		{ bottom_left.x + length, bottom_left.y }
	};
	vb = std::make_shared<Buffer>(vertices.size() * sizeof(glm::vec2), (void*)vertices.data());

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	ib = std::make_shared<IndexBuffer>(6, indices);

	vb->SetLayout(layout);
	va->SetBuffer(vb);
	va->SetIndexBuffer(ib);
}
