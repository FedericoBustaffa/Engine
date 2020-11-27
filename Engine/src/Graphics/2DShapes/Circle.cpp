#include "Shapes.h"

Circle::Circle(const glm::vec2& center, float radius)
	: Shape(), center(center.x, center.y, 0.0, 1.0), radius(radius),
	bottom(center.x, center.y - radius, 0.0, 1.0),
	top(center.x, center.y + radius, 0.0, 1.0),
	left(center.x - radius, center.y, 0.0, 1.0),
	right(center.x + radius, center.y, 0.0, 1.0)
{
}