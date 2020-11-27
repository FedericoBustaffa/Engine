#include "Shapes.h"

Triangle::Triangle(const std::vector<glm::vec2>& vertices)
	: Polygon(3, vertices),
	v1(vertices[0].x, vertices[0].y, 0.0, 1.0),
	v2(vertices[1].x, vertices[1].y, 0.0, 1.0),
	v3(vertices[2].x, vertices[2].y, 0.0, 1.0)
{
}