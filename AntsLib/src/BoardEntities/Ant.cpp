#include <AntsLib/BoardEntities/Ant.hpp>
#include <AntsLib/Core/Settings.hpp>
#include <AntsLib/Stats/Stats.hpp>


const float Ant::discount = 0.99f;
const float Ant::learningRate = 0.000001f;

void Ant::createSprite()
{
	auto texture = TextureLoader::getTexture(TextureLoader::TextureId::ANT_SIMPLIFIED_1x2);
	sprite = sf::Sprite(*texture);
	sprite.setScale(sf::Vector2f(10.f, 10.f));
	sprite.setOrigin(sf::Vector2f((float)texture->getSize().x / 2.f, (float)texture->getSize().y / 2.f));
}

void Ant::updateSprite()
{
	auto positionInTiles = sf::Vector2f(position.x + 0.5f, position.y + 0.5f);
	sprite.setPosition(positionInTiles * VisualizationParams::tileSizeInPx);
	sprite.setRotation((float)180 - getRotationInDegrees());
}

int Ant::getRotationInDegrees() const
{
	return rotationInDegrees;
}

Vector2i Ant::findEmptyPlaceClosestTo(const Vector2i & startingPosition, const Board & board)
{
	auto result = startingPosition;
	while (board.getTileOnPosition(result).isEntityOnTile())
	{
		result.x += 1;
		if (!board.isPositionOnBoard(result))
			throw std::exception("Couldn't find a place for new Ant on board");
	}
	return result;
}

Vector2i Ant::getPositionInFront() const
{
	return position + GeometryCalculator::getDirectionToAdjacentTile(rotationInDegrees);
}

Vector2i Ant::getPositionBehind() const
{
	return position + GeometryCalculator::getDirectionToAdjacentTile(rotationInDegrees + 180);
}

void Ant::rotate(int degrees)
{
	rotationInDegrees += 360 + degrees;
	rotationInDegrees %= 360;
	useEnergy(1);
}

void Ant::gatherFood(Board & board)
{
	auto foodUnderAnt = board.getTileOnPosition(position).content.getValue(GroundContent::FOOD);
	float eatenFood = RangeCalculator::trim(foodUnderAnt).toBeLessThan(AntState::FOOD_FROM_TILE_PER_BITE);
	board.getTileOnPosition(position).content.setValueOf(GroundContent::FOOD, foodUnderAnt - eatenFood);
	giveFood(eatenFood * AntState::MAX_FOOD_ON_TILE);
	rewardFromLastAction = eatenFood * 300;
	Stats::addFoodGathered(eatenFood);
}

void Ant::moveForward(Board & board)
{
	Vector2i newPosition = getPositionInFront();
	if (board.isPositionOnBoard(newPosition) && !board.getTileOnPosition(newPosition).isEntityOnTile())
	{
		board.getTileOnPosition(position).unsetEntityOnTileId();
		board.getTileOnPosition(newPosition).setEntityOnTileId(id);
		position = newPosition;
	}
	useEnergy(1);
}

void Ant::placeSignal(GroundContent::Type signalType, Board & board)
{
	board.getTileOnPosition(position).content.addValueTo(signalType, 0.7f);
}

void Ant::useEnergy(int energy)
{
	if (state.getEnergy() < energy)
	{
		state.setEnergy(1000);
	}
	else
		state.setEnergy(state.getEnergy() - energy);
}

Ant::Ant(Vector2i startingPosition, std::shared_ptr<AntQBrain> brain, int id, int teamId) :
	state(AntState::MaxHpAndEnergyStats())
{
	position = startingPosition;
	this->brain = brain;
	this->id = id;
	this->teamId = teamId;
	createSprite();
}

void Ant::placeNewAntOnBoard(Vector2i startingPosition, std::shared_ptr<AntQBrain> brain, int teamId, Board & board)
{
	startingPosition = Ant::findEmptyPlaceClosestTo(startingPosition, board);
	int newId = board.getNextAvailableId();
	board.getTileOnPosition(startingPosition).setEntityOnTileId(newId);
	board.addEntity(std::make_shared<Ant>(startingPosition, brain, newId, teamId));
}


Ant::Decision Ant::getRandomDecision() const
{
	return (Decision)RandomGenerator::getRandomIntBetween(0, 4);
}

Ant::Decision Ant::getBestDecision(const ValuesArray& qValues) const
{
	Decision bestDecision = Decision(0);
	float maxValue = qValues[0];
	for (int i = 1; i < qValues.getSize(); i++) {
		if (qValues[i] > maxValue) {
			bestDecision = Decision(i);
			maxValue = qValues[i];
		}
	}
	return bestDecision;
}

float Ant::getChanceForExploration() const
{
	return RangeCalculator::trim(1.f - state.cyclesAlive / 5000.f).toInbetween(0.1f, 1.f);
}

Ant::Decision Ant::getDecision(const ValuesArray& qValues) const
{
	if (RandomGenerator::chooseTrueOfFalse(getChanceForExploration()))
	{
		Stats::addOneRandomDecision();
		return getRandomDecision();
	}
	Stats::addOneBrainDecision();
	return getBestDecision(qValues);
}

void Ant::executeDecision(Ant::Decision decision, Board& board)
{
	rewardFromLastAction = 0.f;
	switch(decision)
	{
		case Decision::GATHER_FOOD: gatherFood(board); break;
		case Decision::MOVE_FORWARD: moveForward(board); break;
		case Decision::ROTATE_LEFT: rotate(-45); break;
		case Decision::ROTATE_RIGHT: rotate(45); break;
	}
}

void Ant::learn(const ValuesArray& inputs, const Ant::Decision& decision, const ValuesArray& qValuesOfPrevState, const ValuesArray& qValuesOfCurrState)
{
	if (!Settings::isLearningOn)
		return;
	auto set = TrainingSet(inputs, qValuesOfPrevState);
	float maxOfQValues = qValuesOfCurrState[0];
	for (int i = 1; i < qValuesOfCurrState.getSize(); i++)
		if (qValuesOfCurrState[i] > maxOfQValues)
			maxOfQValues = qValuesOfCurrState[i];
	set.expectedOutput[int(decision)] = discount * maxOfQValues + rewardFromLastAction;
	brain->adjustParameters(std::vector<TrainingSet>({ set }), learningRate);
}

void Ant::performAction(Board & board)
{
	if (isDead())
		return;
	auto inputs = brain->createInputs(board, position, rotationInDegrees, state);
	auto qValuesOfPrevState = brain->createQValuesFromInputs(inputs);
	auto decision = getDecision(qValuesOfPrevState);
	executeDecision(decision, board);
	auto qValuesOfCurrState = brain->createQValuesFromInputs(brain->createInputs(board, position, rotationInDegrees, state));
	learn(inputs, decision, qValuesOfPrevState, qValuesOfCurrState);

	state.cyclesAlive++;
}

BoardEntityType Ant::getEntityType() const
{
	return BoardEntityType::ANT;
}

int Ant::getTeamId() const
{
	return teamId;
}

int Ant::getId() const
{
	return id;
}

void Ant::drawOn(sf::RenderTarget & target)
{
	if (isDead())
		return;
	updateSprite();
	target.draw(sprite);
}

void Ant::damage(int damage)
{
	state.setHp(state.getHp() - damage);
}

void Ant::giveFood(int food)
{
	state.setStoredFood(state.getStoredFood() + food);
}

bool Ant::isDead() const
{
	return state.getHp() <= 0;
}

void Ant::eraseItselfFromBoard(Board & board)
{
	board.getTileOnPosition(position).unsetEntityOnTileId();
}

void Ant::setTeamId(int newTeamId)
{
	teamId = newTeamId;
}
