#pragma once
#include <iostream>
#include <math.h>

class Vector2DInt
{
public:
	int x;
	int y;

	Vector2DInt();
	Vector2DInt(int x, int y);

};


class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator++();
	//Vector2D& Multiply(float x);
	friend Vector2D& operator-(Vector2D v1, const Vector2DInt v2);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

