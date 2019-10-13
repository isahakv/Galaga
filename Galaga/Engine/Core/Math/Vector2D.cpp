#include "Vector2D.h"

void Vector2D::operator+=(const Vector2D& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vector2D::operator-=(const Vector2D& vec)
{
	x -= vec.x;
	y -= vec.y;
}
