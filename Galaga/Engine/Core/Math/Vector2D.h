#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D
{
	float x;
	float y;
	Vector2D() : x(0), y(0) {}
	Vector2D(float x, float y) : x(x), y(y) {}

	float GetSqrMagnitude() const;
	float GetMagnitude() const;

	void operator+=(const Vector2D& vec);
	void operator-=(const Vector2D& vec);

	// Shorten for Vector2D(0.f, 0.f).
	static Vector2D Zero;
	// Shorten for Vector2D(1.f, 0.f).
	static Vector2D Right;
	// Shorten for Vector2D(0.f, 1.f).
	static Vector2D Up;

	void RotateVector(float angle);
	static Vector2D RotateVector(const Vector2D& vec, float angle);

	friend Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2);

	friend Vector2D operator*(const Vector2D& vec, float val);
	friend Vector2D operator/(const Vector2D& vec, float val);
};

#endif // !VECTOR2D_H
