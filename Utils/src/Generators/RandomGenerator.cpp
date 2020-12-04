#include <Utils/Generators/RandomGenerator.hpp>

void RandomGenerator::setSeed(int seed) {
	srand(seed);
}

float RandomGenerator::getRandomFloatBetween(float min, float max) {
	float range = max - min;
	return rand() / (RAND_MAX / (range)) + min;
}

int RandomGenerator::getRandomIntBetween(int inclusiveMin, int exclusiveMax)
{
	int range = exclusiveMax - inclusiveMin;
	return (rand() % range) + inclusiveMin;
}

int RandomGenerator::chooseZeroOrOne(float probabilityOfOne)
{
	return probabilityOfOne >= getRandomFloatBetween(0.f, 1.f) ? 1 : 0;
}

bool RandomGenerator::chooseTrueOfFalse(float probabilityOfTrue)
{
	return probabilityOfTrue >= getRandomFloatBetween(0.f, 1.f) ? true : false;
}