#include "Render.h"

#include <vector>
#include <GL/glew.h>

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

void Render::DrawIndexed(const std::shared_ptr<Polygon>& poly)
{
	poly->GetVA()->Bind();
	int count = (int)poly->GetVA()->GetIndexCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void Render::DrawCircle(const glm::vec2& center, float radius)
{
	int precision = 70;
	float step = 360.0f / precision;
	float angle = step;

	glm::vec2 v1 = { center.x + radius, center.y };
	float x = center.x + radius * glm::cos(glm::radians(angle));
	float y = center.y + radius * glm::sin(glm::radians(angle));
	glm::vec2 v2 = { x, y };

	for (int i = 0; i < precision; i++)
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(center.x, center.y);
		glVertex2f(v1.x, v1.y);
		glVertex2f(v2.x, v2.y);
		glEnd();

		angle += step;
		v1.x = v2.x;
		v1.y = v2.y;
		v2.x = center.x + radius * glm::cos(glm::radians(angle));
		v2.y = center.y + radius * glm::sin(glm::radians(angle));
	}
}

void Render::DrawCircle(const std::shared_ptr<Circle>& circle)
{
	glm::vec2 center = circle->GetCenter();
	float radius = circle->GetRadius();
}
