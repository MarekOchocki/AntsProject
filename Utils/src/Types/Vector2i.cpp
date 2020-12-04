#include "Utils/Types/Vector2i.hpp"

Vector2i Vector2i::operator*(int multiplicant) const
{
	return Vector2i(x*multiplicant, y*multiplicant);
}

Vector2i Vector2i::operator+(const Vector2i & other) const
{
	return Vector2i(x + other.x, y + other.y);
}

Vector2i Vector2i::operator-(const Vector2i & other) const
{
	return Vector2i(x - other.x, y - other.y);
}

Vector2f Vector2i::operator+(const Vector2f & other) const
{
	return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2i::operator-(const Vector2f & other) const
{
	return Vector2f(x - other.x, y - other.y);
}

Vector2i Vector2i::operator/(int divisor) const
{
	return Vector2i(x / divisor, y / divisor);
}

Vector2f Vector2i::operator/(float divisor) const
{
	return Vector2f(x / divisor, y / divisor);
}

void Vector2i::operator*=(int multiplicant)
{
	x *= multiplicant;
	y *= multiplicant;
}

void Vector2i::operator+=(const Vector2i & other)
{
	x += other.x;
	y += other.y;
}

void Vector2i::operator-=(const Vector2i & other)
{
	x -= other.x;
	y -= other.y;
}

void Vector2i::operator/=(int divisor)
{
	x /= divisor;
	y /= divisor;
}

bool Vector2i::operator==(const Vector2i& other) const
{
	return x == other.x && y == other.y;
}

bool Vector2i::operator!=(const Vector2i& other) const
{
	return !(x == other.x && y == other.y);
}
