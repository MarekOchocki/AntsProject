#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include <math.h>

#include <SFML/Graphics.hpp>

#include <ANN.hpp>
#include <Utils.hpp>
#include <AntsLib.hpp>

int main()
{
	RandomGenerator::setSeed(123125);
	std::shared_ptr<Environment> e = std::make_shared<SingleColonyEnvironment>(Vector2i(200, 200), 30);
	Simulation s(e);
	s.start();

	return 0;
}