#pragma once

class Vector2f {
public:
	float x;
	float y;

	Vector2f() = default;
	Vector2f(float x, float y) : x(x), y(y) {};
	Vector2f operator*(float multiplicant);
	Vector2f operator+(const Vector2f &other);
	Vector2f operator-(const Vector2f &other);
	void operator*=(float multiplicant);
	void operator+=(const Vector2f &other);
	void operator-=(const Vector2f &other);
};