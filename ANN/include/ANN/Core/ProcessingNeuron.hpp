#pragma once
#include <ANN/Core/Neuron.hpp>
#include <ANN/Core/Synapse.hpp>

class Synapse;

class ProcessingNeuron : public Neuron {
private:
	float sumOfInputs;

protected:
	float derivative;

	float getCostOverOutputValueDerivative() const;

public:
	float bias;
	std::vector<std::shared_ptr<Synapse>> inputConnections;
	std::vector<std::shared_ptr<Synapse>> outputConnections;

	ProcessingNeuron();
	void shiftBias(float diff);
	void addInputConnection(std::shared_ptr<Synapse> synapse);
	void addOutputConnection(std::shared_ptr<Synapse> synapse);

	float getCostOverInputsSumDerivative() const;
	void updateCostOverInputsSumDerivative(const float & expectedOutputValue);

	virtual void updateCostOverInputsSumDerivative() = 0;
	virtual void updateOutputValue() = 0;
};