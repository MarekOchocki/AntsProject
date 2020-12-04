#pragma once
#include <vector>

#include <ANN/Core.hpp>

class LayeredNeuralNetwork : public StatelessNeuralNetwork {
	friend class LayeredNeuralNetworkBuilder;

private:
	class CostFunctionGradient {
	public:
		std::vector<std::vector<float>> weightChanges;
		std::vector<std::vector<float>> biasChanges;
	};

private:
	std::vector<std::shared_ptr<Receptor>> inputLayer;
	std::vector<std::vector<std::shared_ptr<ProcessingNeuron>>> processingNeuronLayers;
	std::vector<std::vector<std::shared_ptr<Synapse>>> synapseInterLayers;

	void setInputLayerValues(const ValuesArray & inputValues);
	void propagateSignalThroughLayers();
	ValuesArray getLastLayerValues() const;

	CostFunctionGradient makeCostGradient() const;
	void updateCostGradientForTrainingSet(CostFunctionGradient & gradient, const TrainingSet & trainingSet);
	void setLastLayerCostDerivatives(const TrainingSet & trainingSet);
	void updateDerivativesThroughoutNetwork();
	void updateCostFunctionGradient(CostFunctionGradient & gradient) const;
	void applyNegativeCostFunctionGradient(CostFunctionGradient & gradient);
	void adjustGradientToLearningRateAndSetsNumber(CostFunctionGradient & gradient, float learningRate) const;

public:
	virtual ValuesArray getOutputValues(const ValuesArray & inputValues) override;
	void adjustParameters(const std::vector<TrainingSet> & trainingSets, const float & learningRate);
	double getMeanError(const std::vector<TrainingSet>& trainingSets);
};