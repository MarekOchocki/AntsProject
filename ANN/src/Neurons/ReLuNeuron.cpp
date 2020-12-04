#include <ANN/Neurons/ReLuNeuron.hpp>

void ReLuNeuron::updateOutputValue()
{
	float sumOfInputs = bias;
	for (auto s : inputConnections)
		sumOfInputs += s->getWeightedPreviouseNeuronOutput();
	outputValue = sumOfInputs > 0 ? sumOfInputs : 0;
}

void ReLuNeuron::updateCostOverInputsSumDerivative()
{
	derivative = outputValue > 0 ? getCostOverOutputValueDerivative() : 0;
}
