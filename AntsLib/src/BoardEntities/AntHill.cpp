#include <AntsLib/BoardEntities/AntHill.hpp>

const Vector2i AntHill::AntHillSize = Vector2i(15, 15);

void AntHill::createSprite()
{
	auto texture = TextureLoader::getTexture(TextureLoader::TextureId::ANTHILL_50x50);
	sprite = sf::Sprite(*texture);
	sf::Vector2f scale;
	scale.x = (AntHillSize.x * VisualizationParams::tileSizeInPx) / texture->getSize().x;
	scale.y = (AntHillSize.y * VisualizationParams::tileSizeInPx) / texture->getSize().y;
	sprite.setScale(scale);
	sprite.setOrigin(sf::Vector2f((float)texture->getSize().x / 2.f, (float)texture->getSize().y / 2.f));
}

void AntHill::updateSprite()
{
	auto positionInPixels = (topLeftPosition + (AntHillSize / 2.f)) * VisualizationParams::tileSizeInPx;
	sprite.setPosition(positionInPixels.x, positionInPixels.y);
}

bool AntHill::isPlaceCorrectToPlaceAntHill(const Vector2i & topLeftCornerPosition, const Board & board)
{
	for(int x = topLeftCornerPosition.x; x < topLeftCornerPosition.x + AntHillSize.x; x++)
		for (int y = topLeftCornerPosition.y; y < topLeftCornerPosition.y + AntHillSize.y; y++)
			if (!board.isPositionOnBoard(x, y) || board.getTileOnPosition(x, y).isEntityOnTile())
				return false;
	return true;

}

void AntHill::fillTilesOnBoardWithId(const Vector2i & topLeftCornerPosition, int id, Board & board)
{
	for (int x = topLeftCornerPosition.x; x < topLeftCornerPosition.x + AntHillSize.x; x++)
		for (int y = topLeftCornerPosition.y; y < topLeftCornerPosition.y + AntHillSize.y; y++)
			board.getTileOnPosition(x, y).setEntityOnTileId(id);
}

Vector2i AntHill::findEmptyPlaceForTopLeftCornerOfAntHill(const Vector2i & startingPosition, const Board & board)
{
	auto currentCheckingPosition = startingPosition - AntHillSize / 2;
	bool isPositionAvailable = AntHill::isPlaceCorrectToPlaceAntHill(currentCheckingPosition, board);
	while (!isPositionAvailable)
	{
		currentCheckingPosition.x += 1;
		isPositionAvailable = AntHill::isPlaceCorrectToPlaceAntHill(currentCheckingPosition, board);
	}
	return currentCheckingPosition;
}

AntHill::AntHill(Vector2i positionOnBoard, int id, int teamId, int startingEnergy)
{
	topLeftPosition = positionOnBoard;
	this->id = id;
	this->teamId = teamId;
	energy = startingEnergy;
	this->sharedBrain = std::make_shared<AntQBrain>();
	createSprite();
}

void AntHill::placeNewAntHillOnBoard(Vector2i startingPosition, int teamId, int startingEnergy, Board & board)
{
	auto topLeftPosition = AntHill::findEmptyPlaceForTopLeftCornerOfAntHill(startingPosition, board);
	int newId = board.getNextAvailableId();
	AntHill::fillTilesOnBoardWithId(topLeftPosition, newId, board);
	board.addEntity(std::make_shared<AntHill>(AntHill(topLeftPosition, newId, teamId, startingEnergy)));
}

void AntHill::drawOn(sf::RenderTarget & target)
{
	updateSprite();
	target.draw(sprite);
}

void AntHill::performAction(Board & board)
{
	if (energy >= 100 && RandomGenerator::chooseTrueOfFalse(0.1f))
	{
		Ant::placeNewAntOnBoard(topLeftPosition, sharedBrain, teamId, board);
		energy -= 100;
	}
	cyclesPassed++;
}

BoardEntityType AntHill::getEntityType() const
{
	return BoardEntityType::ANTHILL;
}

int AntHill::getTeamId() const
{
	return teamId;
}

int AntHill::getId() const
{
	return id;
}

void AntHill::setTeamId(int newTeamId)
{
	teamId = newTeamId;
}

void AntHill::damage(int damage)
{
	return;
}

void AntHill::giveFood(int food)
{
	energy += food * 10;
}

bool AntHill::isDead() const
{
	return false;
}

void AntHill::eraseItselfFromBoard(Board & board)
{
	return;
}
