#include "Shapes.h"

Triangle::Triangle(const std::vector<glm::vec2>& vertices)
	: Polygon(3, vertices), v1(vertices[0]), v2(vertices[1]), v3(vertices[2])
{
	if (vertices.size() != 3)
		return;
}