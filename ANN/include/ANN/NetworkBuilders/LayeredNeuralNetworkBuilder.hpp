#pragma once

#include <ANN/NeuralNetworks/LayeredNeuralNetwork.hpp>

class LayeredNeuralNetworkBuilder {
private:
	std::vector<int> layerSizes;
	LayeredNeuralNetwork result;

	void connectHiddenLayers(const std::vector<std::shared_ptr<ProcessingNeuron>>& prevLayer, std::vector<std::shared_ptr<ProcessingNeuron>> nextLayer);
	void makeInputLayerNeurons();
	void makeProcessingLayerNeurons();
	void connectInputLayerWithSecondLayer();
	void connectProcessingNeuronLayers();
public:
	LayeredNeuralNetworkBuilder() = default;
	void addLayer(int size);
	LayeredNeuralNetwork build();
};