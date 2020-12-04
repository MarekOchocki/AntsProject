#include <ANN/Core/TrainingSet.hpp>

TrainingSet::TrainingSet(ValuesArray input, ValuesArray expectedOutput)
{
	this->input = input;
	this->expectedOutput = expectedOutput;
}