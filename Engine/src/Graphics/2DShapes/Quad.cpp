#include "Shapes.h"

// quadrilatero generico
Quad::Quad(const std::vector<glm::vec2>& vertices)
	: Polygon(4, vertices)
{
}


// rettangolo
Rectangle::Rectangle(const glm::vec2& bottom_left, const glm::vec2& top_right)
	: Quad({
			bottom_left,
			{ bottom_left.x, top_right.y },
			top_right,
			{ top_right.x, bottom_left.y }
		}),
		bottom_left(bottom_left), top_right(top_right)
{
}

// quadrato
Square::Square(const glm::vec2& bottom_left, float length)
	: Rectangle(bottom_left, { bottom_left.x + length, bottom_left.y + length }),
	bottom_left(bottom_left), length(length)
{
}