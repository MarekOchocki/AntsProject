#include <ANN/NeuralNetworks/LayeredNeuralNetwork.hpp>

void LayeredNeuralNetwork::setInputLayerValues(const ValuesArray & inputValues)
{
	for (int i = 0; i < inputLayer.size(); i++)
		inputLayer[i]->setOutputValue(inputValues[i]);
}

void LayeredNeuralNetwork::propagateSignalThroughLayers()
{
	for (auto layer : processingNeuronLayers)
		for (auto neuron : layer)
			neuron->updateOutputValue();
}

ValuesArray LayeredNeuralNetwork::getLastLayerValues() const
{
	ValuesArray output = ValuesArray();
	for (auto neuron : processingNeuronLayers.back())
		output.pushValue(neuron->getOutputValue());
	return output;
}

void LayeredNeuralNetwork::setLastLayerCostDerivatives(const TrainingSet & trainingSet)
{
	auto outputValues = getOutputValues(trainingSet.input);
	for (int j = 0; j < trainingSet.expectedOutput.getSize(); j++)
		processingNeuronLayers.back()[j]->updateCostOverInputsSumDerivative(trainingSet.expectedOutput[j]);
}

void LayeredNeuralNetwork::updateDerivativesThroughoutNetwork()
{
	for (int j = processingNeuronLayers.size() - 2; j >= 0; j--)
		for (auto neuron : processingNeuronLayers[j])
			neuron->updateCostOverInputsSumDerivative();
}

void LayeredNeuralNetwork::updateCostFunctionGradient(CostFunctionGradient & gradient) const
{
	for (int i = 0; i < synapseInterLayers.size(); i++)
		for (int j = 0; j < synapseInterLayers[i].size(); j++)
			gradient.weightChanges[i][j] += synapseInterLayers[i][j]->getCostoverWeightDerivative();

	for (int i = 0; i < processingNeuronLayers.size(); i++)
		for (int j = 0; j < processingNeuronLayers[i].size(); j++)
			gradient.biasChanges[i][j] += processingNeuronLayers[i][j]->getCostOverInputsSumDerivative();
}

void LayeredNeuralNetwork::applyNegativeCostFunctionGradient(CostFunctionGradient & gradient)
{
	for (int i = 0; i < synapseInterLayers.size(); i++)
		for (int j = 0; j < synapseInterLayers[i].size(); j++)
			synapseInterLayers[i][j]->shiftWeight(-gradient.weightChanges[i][j]);


	for (int i = 0; i < processingNeuronLayers.size(); i++)
		for (int j = 0; j < processingNeuronLayers[i].size(); j++)
			processingNeuronLayers[i][j]->shiftBias(-gradient.biasChanges[i][j]);
}

void LayeredNeuralNetwork::adjustGradientToLearningRateAndSetsNumber(CostFunctionGradient & gradient, float learningRate) const
{
	for (int i = 0; i < synapseInterLayers.size(); i++)
		for (int j = 0; j < synapseInterLayers[i].size(); j++)
			gradient.weightChanges[i][j] *= learningRate;

	for (int i = 0; i < processingNeuronLayers.size(); i++)
		for (int j = 0; j < processingNeuronLayers[i].size(); j++)
			gradient.biasChanges[i][j] *= learningRate;
}

ValuesArray LayeredNeuralNetwork::getOutputValues(const ValuesArray & inputValues)
{
	setInputLayerValues(inputValues);
	propagateSignalThroughLayers();
	return getLastLayerValues();
}

LayeredNeuralNetwork::CostFunctionGradient LayeredNeuralNetwork::makeCostGradient() const
{
	CostFunctionGradient gradient = CostFunctionGradient();

	for (auto synapseLayer : synapseInterLayers)
		gradient.weightChanges.push_back(std::vector<float>(synapseLayer.size()));

	for (auto processingLayer : processingNeuronLayers)
		gradient.biasChanges.push_back(std::vector<float>(processingLayer.size()));

	return gradient;
}

void LayeredNeuralNetwork::updateCostGradientForTrainingSet(CostFunctionGradient & gradient, const TrainingSet & trainingSet)
{
	setLastLayerCostDerivatives(trainingSet);
	updateDerivativesThroughoutNetwork();
	updateCostFunctionGradient(gradient);
}

void LayeredNeuralNetwork::adjustParameters(const std::vector<TrainingSet>& trainingSets, const float & learningRate)
{
	auto gradient = makeCostGradient();

	for (auto trainingSet : trainingSets)
		updateCostGradientForTrainingSet(gradient, trainingSet);

	adjustGradientToLearningRateAndSetsNumber(gradient, learningRate);
	applyNegativeCostFunctionGradient(gradient);
}

double LayeredNeuralNetwork::getMeanError(const std::vector<TrainingSet>& trainingSets)
{
	double sumOfError = 0.0;
	for (auto& set : trainingSets)
	{
		double currentError = 0.0;
		auto outputValues = getOutputValues(set.input);
		for (int j = 0; j < set.expectedOutput.getSize(); j++) {
			double diff = set.expectedOutput[j] - outputValues[j];
			currentError += diff * diff;
		}
		sumOfError += currentError;
	}
	return sumOfError / trainingSets.size();
}