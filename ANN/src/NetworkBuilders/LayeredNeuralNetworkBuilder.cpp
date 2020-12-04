#include <ANN/NetworkBuilders/LayeredNeuralNetworkBuilder.hpp>
#include <ANN/Neurons/SigmoidNeuron.hpp>

void LayeredNeuralNetworkBuilder::makeInputLayerNeurons()
{
	for (int i = 0; i < layerSizes[0]; i++)
	{
		auto receptor = std::make_shared<Receptor>();
		result.inputLayer.push_back(receptor);
	}
}

std::vector<std::shared_ptr<ProcessingNeuron>> makeReLuNeuronLayer(int layerSize)
{
	auto layer = std::vector<std::shared_ptr<ProcessingNeuron>>();
	for (int j = 0; j < layerSize; j++)
		layer.push_back(std::make_shared<ReLuNeuron>());
	return layer;
}

void LayeredNeuralNetworkBuilder::makeProcessingLayerNeurons()
{
	for (int i = 1; i < layerSizes.size(); i++)
		result.processingNeuronLayers.push_back(makeReLuNeuronLayer(layerSizes[i]));
}

std::shared_ptr<Synapse> connectProcessingNeurons(const std::shared_ptr<ProcessingNeuron> & prevNeuron, const std::shared_ptr<ProcessingNeuron> & nextNeuron)
{
	auto synapse = std::make_shared<Synapse>(prevNeuron, nextNeuron);
	nextNeuron->addInputConnection(synapse);
	prevNeuron->addOutputConnection(synapse);
	return synapse;
}

std::shared_ptr<Synapse> connectReceptorToNextNeuron(const std::shared_ptr<Neuron> & inputNeuron, const std::shared_ptr<ProcessingNeuron> & nextNeuron)
{
	auto synapse = std::make_shared<Synapse>(inputNeuron, nextNeuron);
	nextNeuron->addInputConnection(synapse);
	return synapse;
}

void LayeredNeuralNetworkBuilder::connectHiddenLayers(const std::vector<std::shared_ptr<ProcessingNeuron>> & prevLayer, std::vector<std::shared_ptr<ProcessingNeuron>> nextLayer)
{
	result.synapseInterLayers.push_back(std::vector<std::shared_ptr<Synapse>>());
	for (auto prevNeuron : prevLayer)
		for (auto processingNeuron : nextLayer)
			result.synapseInterLayers.back().push_back(connectProcessingNeurons(prevNeuron, processingNeuron));
}

void LayeredNeuralNetworkBuilder::connectInputLayerWithSecondLayer() 
{
	result.synapseInterLayers.push_back(std::vector<std::shared_ptr<Synapse>>());
	for (auto prevNeuron : result.inputLayer)
		for (auto processingNeuron : result.processingNeuronLayers[0])
			result.synapseInterLayers.back().push_back(connectReceptorToNextNeuron(prevNeuron, processingNeuron));
}

void LayeredNeuralNetworkBuilder::connectProcessingNeuronLayers() 
{
	for (int i = 0; i < result.processingNeuronLayers.size() - 1; i++)
		connectHiddenLayers(result.processingNeuronLayers[i], result.processingNeuronLayers[i + 1]);
}

void LayeredNeuralNetworkBuilder::addLayer(int size)
{
	layerSizes.push_back(size);
}

LayeredNeuralNetwork LayeredNeuralNetworkBuilder::build()
{
	result = LayeredNeuralNetwork();

	makeInputLayerNeurons();
	makeProcessingLayerNeurons();
	connectInputLayerWithSecondLayer();
	connectProcessingNeuronLayers();

	return result;
}
