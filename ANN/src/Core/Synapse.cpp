#include <ANN/Core/Synapse.hpp>

Synapse::Synapse(std::shared_ptr<Neuron> previousNeuron, std::shared_ptr<ProcessingNeuron> nextNeuron)
{
	prev = previousNeuron;
	next = nextNeuron;
	weight = RandomGenerator::getRandomFloatBetween(-1, 1);
}

float Synapse::getPreviousNeuronOutput() const
{
	return prev->getOutputValue();
}

float Synapse::getWeightedPreviouseNeuronOutput() const
{
	return prev->getOutputValue() * weight;
}

float Synapse::getNextNeuronCostOverInputsSumDerivative() const
{
	return next->getCostOverInputsSumDerivative();
}

float Synapse::getCostoverWeightDerivative() const
{
	return prev->getOutputValue() * getNextNeuronCostOverInputsSumDerivative();
}

void Synapse::shiftWeight(float diff)
{
	weight += diff;
}

float Synapse::getWeight() const
{
	return weight;
}
