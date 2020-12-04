#pragma once
#include <random>

class RandomGenerator {
public:
	static void setSeed(int seed);

	static float getRandomFloatBetween(float min, float max);
	static int getRandomIntBetween(int inclusiveMin, int exclusiveMax);
	static int chooseZeroOrOne(float probabilityOfOne);
	static bool chooseTrueOfFalse(float probabilityOfTrue);
};