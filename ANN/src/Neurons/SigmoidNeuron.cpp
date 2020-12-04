#include <ANN/Neurons/SigmoidNeuron.hpp>

void SigmoidNeuron::updateOutputValue()
{
	float sumOfInputs = bias;
	for (auto s : inputConnections)
		sumOfInputs += s->getWeightedPreviouseNeuronOutput();

	outputValue = 1 / (1 + std::exp(-sumOfInputs));
}

void SigmoidNeuron::updateCostOverInputsSumDerivative()
{
	derivative = outputValue * (1 - outputValue) * getCostOverOutputValueDerivative();
}
