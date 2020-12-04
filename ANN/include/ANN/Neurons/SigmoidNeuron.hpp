#pragma once
#include <vector>

#include <ANN/Core/Synapse.hpp>

class SigmoidNeuron : public ProcessingNeuron
{
public:
	virtual void updateOutputValue() override;
	virtual void updateCostOverInputsSumDerivative() override;
};