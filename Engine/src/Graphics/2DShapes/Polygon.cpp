#include "Shapes.h"

Polygon::Polygon(int sides)
	: sides(sides), model(1.0), color(0.0)
{
}

Polygon::Polygon(int sides, const std::vector<glm::vec2>& vertices)
	: sides(sides), vertices(vertices), model(1.0), color(0.0)
{
}

void Polygon::SetColor(float red, float green, float blue, float alpha)
{
	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = alpha;
}