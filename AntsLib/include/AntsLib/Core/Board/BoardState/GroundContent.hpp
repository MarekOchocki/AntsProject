#pragma once
#include <vector>

#include <Utils/Calculators.hpp>

class GroundContent {
public:
	enum Type {
		FOOD
	};

private:
	static const int numberOfTypes = 1;
	std::vector<float> values;
	bool hasNonZeroSignals_;

	void checkIfSignalsAreNonZero();

public:
	GroundContent();
	float getValue(const Type & contentType) const;
	void setValueOf(const Type & contentType, float newValue);
	void addValueTo(const Type & contentType, float difference);
	void multiplyValueBy(const Type & contentType, float multiplier);
	bool hasNonZeroSignals() const;
};