#include "Shapes.h"

Polygon::Polygon()
	: model(1.0), color(0.0)
{
}

void Polygon::SetColor(float red, float green, float blue, float alpha)
{
	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = alpha;
}