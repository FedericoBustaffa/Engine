#include "Triangle.h"

Triangle::Triangle(size_t size, void* data, const std::shared_ptr<Layout>& layout)
	: model(1.0), move(0.0)
{
	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(size, data);
	uint32_t indices[3] = { 0, 1, 2 };
	ib = std::make_shared<IndexBuffer>(3, indices);

	vb->SetLayout(layout);
	va->AddBuffer(vb);
	va->SetIndexBuffer(ib);
}

const std::shared_ptr<VertexArray>& Triangle::GetVA() const
{
	return va;
}

void Triangle::SetModel(const glm::mat4& model)
{
	this->model = model;
}

const glm::mat4& Triangle::GetModel() const
{
	return model;
}
