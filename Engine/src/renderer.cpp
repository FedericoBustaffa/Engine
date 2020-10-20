#include "Renderer.h"

#include <GL/glew.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::BackgroundColor(float red, float green, float blue)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red, green, blue, 1.0f);
}

void Renderer::Draw(VertexArray& va, const VertexBuffer& vb, const IndexBuffer& ib, const Shader& shader)
{
	va.Bind();
	vb.Bind();
	va.Enable();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	va.Disable();
}