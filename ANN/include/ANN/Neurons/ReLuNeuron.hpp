#pragma once
#include <vector>

#include <ANN/Core/Synapse.hpp>

class ReLuNeuron : public ProcessingNeuron
{
public:
	virtual void updateOutputValue() override;
	virtual void updateCostOverInputsSumDerivative() override;
};