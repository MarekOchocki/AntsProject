#pragma once
#include <Utils/Types.hpp>

#include <AntsLib/Core/Board/BoardState/BoardEntity.hpp>
#include <AntsLib/BoardEntities/Ant.hpp>

class AntHill : public BoardEntity {
private:
	const static Vector2i AntHillSize;
	int energy = 0;
	Vector2i topLeftPosition;
	int id = 0;
	int teamId = 0;
	int cyclesPassed = 0;

	std::shared_ptr<AntQBrain> sharedBrain;

	sf::Sprite sprite;
	std::vector<sf::Sprite> neurons;
	std::vector<sf::Sprite> synapses;

	void createSprite();
	void updateSprite();

	static bool isPlaceCorrectToPlaceAntHill(const Vector2i & topLeftCornerPosition, const Board&board);
	static void fillTilesOnBoardWithId(const Vector2i & topLeftCornerPosition, int id, Board& board);
	static Vector2i findEmptyPlaceForTopLeftCornerOfAntHill(const Vector2i & startingPosition, const Board& board);
	AntHill(Vector2i positionOnBoard, int id, int teamId, int startingEnergy);
public:
	static void placeNewAntHillOnBoard(Vector2i startingPosition, int teamId, int startingEnergy, Board & board);

	virtual void drawOn(sf::RenderTarget & target) override;
	virtual void performAction(Board & board) override;
	virtual BoardEntityType getEntityType() const override;
	virtual int getTeamId() const override;
	virtual int getId() const override;
	virtual void setTeamId(int newTeamId) override;

	virtual void damage(int damage) override;
	virtual void giveFood(int food) override;
	virtual bool isDead() const override;
	virtual void eraseItselfFromBoard(Board & board) override;
};