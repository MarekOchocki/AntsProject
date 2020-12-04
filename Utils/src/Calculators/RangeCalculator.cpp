#include <Utils/Calculators/RangeCalculator.hpp>

TrimValueFloat::TrimValueFloat(float value)
{
	this->value = value;
}

float TrimValueFloat::toBeGreaterThan(float min)
{
	return value < min ? min : value;
}

float TrimValueFloat::toBeLessThan(float max)
{
	return value > max ? max : value;
}

float TrimValueFloat::toInbetween(float min, float max)
{
	value = toBeLessThan(max);
	return toBeGreaterThan(min);
}

TrimValueInt::TrimValueInt(int value)
{
	this->value = value;
}

int TrimValueInt::toBeGreaterOrEqualThan(int min)
{
	return value < min ? min : value;
}

int TrimValueInt::toBeLessOrEqualThan(int max)
{
	return value > max ? max : value;
}

int TrimValueInt::toInbetweenInclusive(int min, int max)
{
	int val = toBeGreaterOrEqualThan(min);
	return val > max ? max : val;
}

TrimValueFloat RangeCalculator::trim(float value)
{
	return TrimValueFloat(value);
}

TrimValueInt RangeCalculator::trim(int value)
{
	return TrimValueInt(value);
}

bool RangeCalculator::isInRange(int value, int inclusiveMin, int exclusiveMax)
{
	return (value >= inclusiveMin) && (value < exclusiveMax);
}

bool RangeCalculator::isInRange(float value, float inclusiveMin, float exclusiveMax)
{
	return value >= inclusiveMin && value < exclusiveMax;
}
