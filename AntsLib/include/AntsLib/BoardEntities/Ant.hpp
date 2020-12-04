#pragma once
#include <exception>

#include <Utils/Calculators/GeometryCalculator.hpp>
#include <ANN.hpp>

#include <AntsLib/Core/Board/BoardState/BoardEntity.hpp>
#include <AntsLib/BoardEntities/Ant/AntState.hpp>
#include <AntsLib/BoardEntities/Ant/AntQBrain.hpp>
#include <AntsLib/Visualization/TextureLoader.hpp>
#include <AntsLib/Visualization/VisualizationParams.hpp>

class Ant : public BoardEntity{
private:
	enum class Decision {
		GATHER_FOOD,
		ROTATE_LEFT,
		ROTATE_RIGHT,
		MOVE_FORWARD
	};
	static const float discount;
	static const float learningRate;

private:
	Vector2i position;
	int rotationInDegrees = 0;
	AntState state;
	int id = 0;
	int teamId = 0;
	float rewardFromLastAction = 0.f;

	std::shared_ptr<AntQBrain> brain;

	sf::Sprite sprite;

	void createSprite();
	void updateSprite();

	int getRotationInDegrees() const;
	static Vector2i findEmptyPlaceClosestTo(const Vector2i & startingPosition, const Board& board);

	Vector2i getPositionInFront() const;
	Vector2i getPositionBehind() const;
	void rotate(int degrees);
	void gatherFood(Board& board);
	void eatFood();
	void moveForward(Board& board);
	void placeSignal(GroundContent::Type signalType, Board& board);
	void useEnergy(int energy);

	Decision getRandomDecision() const;
	Decision getBestDecision(const ValuesArray& qValues) const;
	float getChanceForExploration() const;
	Decision getDecision(const ValuesArray& qValues) const;
	void executeDecision(Ant::Decision decision, Board& board);
	void placeSignalBasedOnGatheredFood(Board& board);

	void learn(const ValuesArray& inputs, const Decision& decision, const ValuesArray& qValuesOfPrevState, const ValuesArray& qValuesOfCurrState);
public:
	Ant(Vector2i startingPosition, std::shared_ptr<AntQBrain> brain, int id, int teamId);
	static void placeNewAntOnBoard(Vector2i startingPosition, std::shared_ptr<AntQBrain> brain, int teamId, Board & board);
	
	virtual void performAction(Board & board) override;
	virtual BoardEntityType getEntityType() const override;
	virtual int getTeamId() const override;
	virtual int getId() const override;
	virtual void setTeamId(int newTeamId) override;
	virtual void drawOn(sf::RenderTarget & target) override;

	virtual void damage(int damage) override;
	virtual void giveFood(int food) override;
	virtual bool isDead() const override;
	virtual void eraseItselfFromBoard(Board & board) override;
};