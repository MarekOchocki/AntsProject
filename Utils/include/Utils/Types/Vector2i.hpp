#pragma once
#include "./Vector2f.hpp"

class Vector2i {
public:
	int x;
	int y;

	Vector2i() = default;
	Vector2i(int x, int y) : x(x), y(y) {};
	Vector2i operator*(int multiplicant) const;
	Vector2i operator+(const Vector2i &other) const;
	Vector2i operator-(const Vector2i &other) const;
	Vector2f operator+(const Vector2f &other) const;
	Vector2f operator-(const Vector2f &other) const;
	Vector2i operator/(int divisor) const;
	Vector2f operator/(float divisor) const;
	void operator*=(int multiplicant);
	void operator+=(const Vector2i &other);
	void operator-=(const Vector2i &other);
	void operator/=(int divisor);
	bool operator==(const Vector2i& other) const;
	bool operator!=(const Vector2i& other) const;
};