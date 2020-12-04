#pragma once
#include <ANN/Core/Neuron.hpp>

class Receptor : public Neuron{

public:
	void setOutputValue(float newValue);
};