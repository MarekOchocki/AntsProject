#pragma once
#include <ANN/Core/ValuesArray.hpp>

class TrainingSet {
public:
	ValuesArray input;
	ValuesArray expectedOutput;

	TrainingSet() = default;
	TrainingSet(ValuesArray input, ValuesArray expectedOutput);
};