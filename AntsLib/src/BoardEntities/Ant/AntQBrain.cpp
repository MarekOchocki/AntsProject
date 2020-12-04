#include <AntsLib/BoardEntities/Ant/AntQBrain.hpp>
#include <iostream>

LayeredNeuralNetwork AntQBrain::createBrain() const
{
	auto builder = LayeredNeuralNetworkBuilder();
	builder.addLayer(INPUTS_NUMBER);
	builder.addLayer(25);
	builder.addLayer(10);
	builder.addLayer(OUTPUTS_NUMBER);
	return builder.build();
}

void AntQBrain::pushInformationsAboutTile(ValuesArray& result, const Board& board, const Vector2i& currentlyCheckingPosition) const
{
	if (board.isPositionOnBoard(currentlyCheckingPosition))
	{
		pushInformationAboutSignals(result, board, currentlyCheckingPosition);
		pushInformationAboutEntities(board, currentlyCheckingPosition, result);
		return;
	}
	pushEmptyInformation(result, 3);
}

void AntQBrain::pushInformationAboutEntities(const Board& board, const Vector2i& currentlyCheckingPosition, ValuesArray& result) const
{
	bool isEntityOnTile = board.getTileOnPosition(currentlyCheckingPosition).isEntityOnTile();
	if (!isEntityOnTile)
		pushEmptyInformation(result, 2);
	else
		pushInformationAboutEntitiesTypes(result, board, currentlyCheckingPosition);
}

void AntQBrain::pushInformationAboutEntitiesTypes(ValuesArray& result, const Board& board, const Vector2i& currentlyCheckingPosition) const
{
	result.pushValue(board.getEntityOnTileType(currentlyCheckingPosition) == BoardEntityType::ANT);
	result.pushValue(board.getEntityOnTileType(currentlyCheckingPosition) == BoardEntityType::ANTHILL);
}

void AntQBrain::pushEmptyInformation(ValuesArray& result, int numberOfEmptyInformation) const
{
	for (int i = 0; i < numberOfEmptyInformation; i++)
		result.pushValue(0.f);
}

void AntQBrain::pushInformationAboutSignals(ValuesArray& result, const Board& board, const Vector2i& currentlyCheckingPosition) const
{
	result.pushValue(board.getTileOnPosition(currentlyCheckingPosition).content.getValue(GroundContent::FOOD));
}

ValuesArray AntQBrain::createInputs(const Board& board, const Vector2i& antPosition, int antRotation, const AntState& antState) const
{
	ValuesArray result;
	result.reserve(INPUTS_NUMBER);
	pushInformationAboutAdjacentTiles(antRotation, antPosition, board, result);
	return result;
}

void AntQBrain::pushInformationAboutAdjacentTiles(int antRotation, const Vector2i& antPosition, const Board& board, ValuesArray& result) const
{
	auto directionVectors = GeometryCalculator::getDirectionsToEveryAdjacentTileClockwise(antRotation);
	for (auto direction : directionVectors)
		pushInformationsAboutTile(result, board, antPosition + direction);
	pushInformationAboutSignals(result, board, antPosition);
}

ValuesArray AntQBrain::createQValuesFromInputs(const ValuesArray& inputs)
{
	auto outputs = getOutputValues(inputs);
	return outputs;
}


void AntQBrain::learnNewSet(const TrainingSet& set)
{
	this->adjustParameters({ set }, 0.000001f);
}

AntQBrain::AntQBrain() : LayeredNeuralNetwork(createBrain())
{
}
