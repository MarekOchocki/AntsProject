#include <AntsLib/Stats/Stats.hpp>
#include <AntsLib/Core/Settings.hpp>
#include <iostream>
#include <fstream>

int Stats::brainDecisions = 0;
int Stats::randomDecisions = 0;
float Stats::foodGathered = 0.f;

void Stats::addOneBrainDecision()
{
	brainDecisions++;
}

void Stats::addOneRandomDecision()
{
	randomDecisions++;
}

void Stats::addFoodGathered(const float& food)
{
	foodGathered += food;
}

void Stats::completeSimulationCycle()
{
	static std::ofstream file;
	if (Settings::outputLogs) {
		std::cout << "\n";
		std::cout << "\nStats: brain     random    gathered\n";
		std::cout << std::left << "Stats: "; std::cout.width(10);
		std::cout << std::left << brainDecisions; std::cout.width(10);
		std::cout << std::left << randomDecisions; std::cout.width(10);
		std::cout << std::left << foodGathered;
	}

	if(!file.is_open())
		file.open("stats_qLearning2.txt", std::ofstream::out | std::ofstream::app);
	file << "\n" << foodGathered;
	file.flush();
	brainDecisions = 0;
	randomDecisions = 0;
	foodGathered = 0;
}
