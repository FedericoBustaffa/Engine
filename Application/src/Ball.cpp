#include "Ball.h"

Ball::Ball(const std::vector<glm::vec4>& buffer)
	: vertices(buffer), speed(10.0f), move(0.0), model(1.0)
{
	// layout
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 4 }
	}));

	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(buffer.size() * sizeof(glm::vec4), (void*)buffer.data());

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	ib = std::make_shared<IndexBuffer>(6, indices);

	vb->SetLayout(layout);
	va->AddBuffer(vb);
	va->SetIndexBuffer(ib);
}

