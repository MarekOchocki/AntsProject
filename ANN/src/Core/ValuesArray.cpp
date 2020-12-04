#include <ANN/Core/ValuesArray.hpp>

ValuesArray::ValuesArray(int size)
{
	values = std::vector<float>(size);
}

void ValuesArray::reserve(int size) {
	values.reserve(size);
}

int ValuesArray::getSize() const {
	return (int) values.size(); 
}

void ValuesArray::pushValue(float newValue) {
	values.push_back(newValue);
}

float & ValuesArray::operator[](int index) {
	return values[index];
}

const float & ValuesArray::operator[](int index) const
{
	return values[index];
}

ValuesArray ValuesArray::operator+(const ValuesArray & second) const
{
	ValuesArray result;
	result.reserve(values.size() + second.getSize());
	for (auto value : values)
		result.pushValue(value);
	for (auto value : second.values)
		result.pushValue(value);
	return result;
}
