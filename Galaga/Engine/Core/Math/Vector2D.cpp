#include "Vector2D.h"
#include <math.h>

Vector2D Vector2D::Zero(0.f, 0.f);
Vector2D Vector2D::Right(1.f, 0.f);
Vector2D Vector2D::Up(0.f, 1.f);

float Vector2D::GetSqrMagnitude() const
{
	return x * x + y * y;
}

float Vector2D::GetMagnitude() const
{
	return (float)sqrt(x * x + y * y);
}

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

void Vector2D::RotateVector(float angle)
{
	float radians = angle * 3.14159f / 180.f;
	x = cos(radians) * x - sin(radians) * y;
	y = sin(radians) * x + cos(radians) * y;
}

Vector2D Vector2D::RotateVector(const Vector2D& vec, float angle)
{
	Vector2D vector(vec);
	vector.RotateVector(angle);
	return vector;
}

Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2)
{
	return Vector2D(vec1.x + vec2.x, vec1.y + vec2.y);
}

Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2)
{
	return Vector2D(vec1.x - vec2.x, vec1.y - vec2.y);
}

Vector2D operator*(const Vector2D& vec, float val)
{
	return Vector2D(vec.x * val, vec.y * val);
}

Vector2D operator/(const Vector2D& vec, float val)
{
	return Vector2D(vec.x / val, vec.y / val);
}
