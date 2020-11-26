#include "Render.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char* Render::GetVendor()
{
	return (const char*)glGetString(GL_VENDOR);
}

const char* Render::GetRenderer()
{
	return (const char*)glGetString(GL_RENDERER);
}

void Render::BackgroundColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::BeginScene()
{
}

void Render::EndScene()
{
}

void Render::DrawIndexed(const std::shared_ptr<VertexArray>& va)
{
	va->Bind();
	glDrawElements(GL_TRIANGLES, (int)va->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}