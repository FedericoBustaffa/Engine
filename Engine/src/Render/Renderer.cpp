#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char* Renderer::GetVendor()
{
	return (const char*)glGetString(GL_VENDOR);
}

const char* Renderer::GetRenderer()
{
	return (const char*)glGetString(GL_RENDERER);
}

void Renderer::BackgroundColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BeginScene()
{
}

void Renderer::EndScene()
{
}

void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& va)
{
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}