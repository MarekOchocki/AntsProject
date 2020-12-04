#pragma once
#include <vector>

#include <ANN/Core/ValuesArray.hpp>
#include <ANN/Neurons/ReLuNeuron.hpp>

class StatelessNeuralNetwork {

public:
	virtual ValuesArray getOutputValues(const ValuesArray & inputValues) = 0;
};