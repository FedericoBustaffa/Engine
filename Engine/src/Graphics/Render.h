#pragma once

#include <memory>

#include "VertexArray.h"
#include "2DShapes/Shapes.h"

class Render
{
public:
	static const char* GetVendor();
	static const char* GetRenderer();
	
	static void BackgroundColor(float red, float green, float blue, float alpha);
	
	static void BeginScene();
	static void EndScene();
	static void DrawIndexed(const std::shared_ptr<VertexArray>& va);
	/*static void DrawQuad(const std::shared_ptr<Square>& square);
	static void DrawQuad(const glm::vec2& bottom_left, float length);
	static void DrawCircle(const std::shared_ptr<Circle>& circle);
	static void DrawCircle(const glm::vec2& center, float radius);*/

private:
	Render() = default;
};