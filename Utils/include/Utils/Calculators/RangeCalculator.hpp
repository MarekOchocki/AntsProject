#pragma once

class TrimValueFloat {
private:
	float value;
public:
	TrimValueFloat(float value);
	float toBeGreaterThan(float min);
	float toBeLessThan(float max);
	float toInbetween(float min, float max);
};

class TrimValueInt {
private:
	int value;
public:
	TrimValueInt(int value);
	int toBeGreaterOrEqualThan(int min);
	int toBeLessOrEqualThan(int max);
	int toInbetweenInclusive(int min, int max);
};

class RangeCalculator {

public:
	static TrimValueFloat trim(float value);
	static TrimValueInt trim(int value);
	static bool isInRange(int value, int inclusiveMin, int exclusiveMax);
	static bool isInRange(float value, float inclusiveMin, float exclusiveMax);
};