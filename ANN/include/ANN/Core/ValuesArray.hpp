#pragma once
#include <vector>

class ValuesArray {
private:
	std::vector<float> values;

public:
	ValuesArray() = default;
	ValuesArray(int size);
	void reserve(int size);
	int getSize() const;
	void pushValue(float newValue);
	float & operator[](int index);
	const float & operator[](int index) const;
	ValuesArray operator+(const ValuesArray & second) const;

};