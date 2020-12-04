#include <Utils/Types/Vector2f.hpp>

Vector2f Vector2f::operator*(float multiplicant)
{
	return Vector2f(x*multiplicant, y*multiplicant);
}

Vector2f Vector2f::operator+(const Vector2f & other)
{
	return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f & other)
{
	return Vector2f(x - other.x, y - other.y);
}

void Vector2f::operator*=(float multiplicant)
{
	x *= multiplicant;
	y *= multiplicant;
}

void Vector2f::operator+=(const Vector2f & other)
{
	x += other.x;
	y += other.y;
}

void Vector2f::operator-=(const Vector2f & other)
{
	x -= other.x;
	y -= other.y;
}
