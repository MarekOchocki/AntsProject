#include <ANN/Core/ProcessingNeuron.hpp>

float ProcessingNeuron::getCostOverOutputValueDerivative() const
{
	float d = 0;
	for (auto synapse : outputConnections)
		d += synapse->getWeight() * synapse->getNextNeuronCostOverInputsSumDerivative();
	return d;
}

ProcessingNeuron::ProcessingNeuron()
{
	bias = RandomGenerator::getRandomFloatBetween(-1, 1);
}

void ProcessingNeuron::shiftBias(float diff)
{
	bias += diff;
}

void ProcessingNeuron::addInputConnection(std::shared_ptr<Synapse> synapse)
{
	inputConnections.push_back(synapse);
}

void ProcessingNeuron::addOutputConnection(std::shared_ptr<Synapse> synapse)
{
	outputConnections.push_back(synapse);
}

float ProcessingNeuron::getCostOverInputsSumDerivative() const
{
	return derivative;
}

void ProcessingNeuron::updateCostOverInputsSumDerivative(const float & expectedOutputValue)
{
	derivative = 2 * (outputValue - expectedOutputValue);
}
