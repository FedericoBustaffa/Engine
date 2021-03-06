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
	static void BackgroundColor(const glm::vec4& color);
	
	static void DrawIndexed(const std::shared_ptr<VertexArray>& va);
	static void DrawPolygon(const std::shared_ptr<Polygon>& poly);
	static void DrawCircle(const glm::vec2& center, float radius);
	static void DrawCircle(const std::shared_ptr<Circle>& circle);

private:
	Render() = default;
};