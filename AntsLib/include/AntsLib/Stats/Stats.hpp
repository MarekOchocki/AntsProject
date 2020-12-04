#pragma once

class Stats {
public:
	static int brainDecisions;
	static int randomDecisions;
	static float foodGathered;

	static void addOneBrainDecision();
	static void addOneRandomDecision();
	static void addFoodGathered(const float& food);
	static void completeSimulationCycle();
};