#pragma once
#include <vector>

#include <ANN.hpp>
#include <Utils.hpp>

#include <AntsLib/Core/Board/Board.hpp>
#include <AntsLib/BoardEntities/Ant/AntState.hpp>

class AntQBrain : public LayeredNeuralNetwork {
private:
	LayeredNeuralNetwork createBrain() const;

	void pushInformationsAboutTile(ValuesArray& result, const Board& board, const Vector2i& currentlyCheckingPosition) const;
	void pushInformationAboutEntities(const Board& board, const Vector2i& currentlyCheckingPosition, ValuesArray& result) const;
	void pushInformationAboutEntitiesTypes(ValuesArray& result, const Board& board, const Vector2i& currentlyCheckingPosition) const;
	void pushEmptyInformation(ValuesArray& result, int numberOfEmptyInformation) const;
	void pushInformationAboutSignals(ValuesArray& result, const Board& board, const Vector2i& currentlyCheckingPosition) const;
	void pushInformationAboutInternalState(ValuesArray& result, const AntState& antState) const;
	void pushInformationAboutAdjacentTiles(int antRotation, const Vector2i& antPosition, const Board& board, ValuesArray& result) const;
public:
	static constexpr int INPUTS_NUMBER = 25;
	static constexpr int OUTPUTS_NUMBER = 4;

	ValuesArray createInputs(const Board& board, const Vector2i& antPosition, int antRotation, const AntState& antState) const;
	ValuesArray createQValuesFromInputs(const ValuesArray& inputs);

	void learnNewSet(const TrainingSet& set);

	AntQBrain();
};