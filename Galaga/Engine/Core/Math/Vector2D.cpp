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

Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2)
{
	return Vector2D(vec1.x + vec2.x, vec1.y + vec2.y);
}

Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2)
{
	return Vector2D(vec1.x - vec2.x, vec1.y - vec2.y);
}

Vector2D operator*(const Vector2D& vec, const float& val)
{
	return Vector2D(vec.x * val, vec.y * val);
}

Vector2D operator/(const Vector2D& vec, const float& val)
{
	return Vector2D(vec.x / val, vec.y / val);
}
