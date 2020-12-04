#include <AntsLib/Core/Board/BoardState/GroundContent.hpp>

GroundContent::GroundContent()
{
	for(int i = 0; i < numberOfTypes; i++)
		values.push_back(0);
	hasNonZeroSignals_ = false;
}

float GroundContent::getValue(const Type & contentType) const
{
	return values[contentType];
}

void GroundContent::checkIfSignalsAreNonZero()
{
	hasNonZeroSignals_ = false;
	for (int i = 0; i < numberOfTypes; i++)
		if (values[i] > 0.001f)
			hasNonZeroSignals_ = true;
}

void GroundContent::setValueOf(const Type & contentType, float newValue)
{
	values[contentType] = RangeCalculator::trim(newValue).toInbetween(0.f, 1.f);
	values[contentType] = values[contentType] <= 0.01f? 0.f : values[contentType];
	checkIfSignalsAreNonZero();
}

void GroundContent::addValueTo(const Type & contentType, float difference)
{
	setValueOf(contentType, values[contentType] + difference);
}

void GroundContent::multiplyValueBy(const Type & contentType, float multiplier)
{
	setValueOf(contentType, values[contentType] * multiplier);
}

bool GroundContent::hasNonZeroSignals() const
{
	return hasNonZeroSignals_;
}