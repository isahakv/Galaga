#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D
{
	float x;
	float y;
	Vector2D() : x(0), y(0) {}
	Vector2D(float x, float y) : x(x), y(y) {}

	void operator+=(const Vector2D& vec);
	void operator-=(const Vector2D& vec);

	friend Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2);

	friend Vector2D operator*(const Vector2D& vec, const float& val);
	friend Vector2D operator/(const Vector2D& vec, const float& val);
};

#endif // !VECTOR2D_H
