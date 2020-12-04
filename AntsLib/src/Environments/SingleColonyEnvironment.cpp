#include <AntsLib/Environments/SingleColonyEnvironment.hpp>
#include <AntsLib/Stats/Stats.hpp>

SingleColonyEnvironment::SingleColonyEnvironment(const Vector2i & boardSize, int startingAntsCount) :
	board(boardSize)
{
	AntHill::placeNewAntHillOnBoard(boardSize / 2 + Vector2i(0, 0), 1, startingAntsCount * 100, board);
}

void SingleColonyEnvironment::perform1Cycle()
{
	board.perform1Cycle();
	Stats::completeSimulationCycle();

	if (RandomGenerator::chooseTrueOfFalse(0.15f))
	{
		auto randomPosition = Vector2i();
		randomPosition.x = RandomGenerator::getRandomIntBetween(0, board.getSize().x);
		randomPosition.y = RandomGenerator::getRandomIntBetween(0, board.getSize().y);
		placeSmallFoodOnPosition(randomPosition);
	}
}


void SingleColonyEnvironment::placeSmallFoodOnPosition(Vector2i &position)
{
	auto directions = GeometryCalculator::getDirectionsToEveryAdjacentTileClockwise(0);
	for (int i = 0; i < directions.size(); i++)
	{
		if (board.isPositionOnBoard(position + directions[i]))
			board.getTileOnPosition(position + directions[i]).content.addValueTo(GroundContent::FOOD, 1.f);
	}
}

void SingleColonyEnvironment::drawOn(sf::RenderTarget & target)
{
	board.drawOn(target);
}
