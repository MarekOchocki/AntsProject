#pragma once
#include <memory>

#include <Utils/Generators.hpp>

#include <ANN/Core/Neuron.hpp>
#include <ANN/Core/ProcessingNeuron.hpp>

class ProcessingNeuron;

class Synapse {
private:

public:
	std::shared_ptr<Neuron> prev;
	std::shared_ptr<ProcessingNeuron> next;
	float weight;

	Synapse(std::shared_ptr<Neuron> previousNeuron, std::shared_ptr<ProcessingNeuron> nextNeuron);
	float getPreviousNeuronOutput() const;
	float getWeightedPreviouseNeuronOutput() const;

	float getNextNeuronCostOverInputsSumDerivative() const;
	float getCostoverWeightDerivative() const;
	
	void shiftWeight(float diff);
	float getWeight() const;
};