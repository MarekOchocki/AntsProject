#pragma once
#include <AntsLib/Core/Environment.hpp>
#include <AntsLib/Core/Board/Board.hpp>
#include <AntsLib/BoardEntities/AntHill.hpp>

class SingleColonyEnvironment : public Environment {
private:
	Board board;

	void placeSmallFoodOnPosition(Vector2i& position);
public:
	SingleColonyEnvironment(const Vector2i & boardSize, int startingAntsCount);
	virtual void perform1Cycle() override;
	virtual void drawOn(sf::RenderTarget & target) override;

};