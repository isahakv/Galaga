#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D
{
	int x;
	int y;
	Vector2D() : x(0), y(0) {}
	Vector2D(int x, int y) : x(x), y(y) {}

	void operator+=(const Vector2D& vec);
	void operator-=(const Vector2D& vec);
};

#endif // !VECTOR2D_H
