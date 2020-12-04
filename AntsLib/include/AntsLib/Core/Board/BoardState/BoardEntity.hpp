#pragma once
#include <Utils/Types.hpp>
#include <SFML/Graphics.hpp>

#include <AntsLib/Core/Board/Board.hpp>
#include <AntsLib/Core/Board/BoardState/BoardEntityType.hpp>

class Board;

class BoardEntity {
public:
	virtual void drawOn(sf::RenderTarget & target) = 0;
	virtual void performAction(Board& board) = 0;
	virtual BoardEntityType getEntityType() const = 0;
	virtual int getTeamId() const = 0;
	virtual int getId() const = 0;
	virtual void setTeamId(int newTeamId) = 0;
	virtual bool isDead() const = 0;
	virtual void eraseItselfFromBoard(Board & board) = 0;

	virtual void damage(int damage) = 0;
	virtual void giveFood(int food) = 0;
};