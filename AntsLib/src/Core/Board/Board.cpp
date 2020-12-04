#include <AntsLib/Core/Board/Board.hpp>

Board::Board(Vector2i size)
{
	this->size = size;
	initTiles();
	initTilesVertexes(tiles);
}

void Board::perform1Cycle()
{

	std::vector<int> idsToErase;
	for (auto entity : entities)
	{
		entity.second->performAction(*this);
		if (entity.second->isDead())
			idsToErase.push_back(entity.second->getId());
	}

	for (auto id : idsToErase)
	{
		entities[id]->eraseItselfFromBoard(*this);
		entities.erase(id);
	}

}
int Board::positionToIndexInTiles(int x, int y) const
{
	return x * size.y + y;
}

Tile & Board::getTileOnPosition(int x, int y)
{
	return tiles[positionToIndexInTiles(x, y)];
}

Tile & Board::getTileOnPosition(const Vector2i & position)
{
	return getTileOnPosition(position.x, position.y);
}

const Tile & Board::getTileOnPosition(int x, int y) const
{
	return tiles[positionToIndexInTiles(x, y)];
}

int Board::getEntityOnTileTeamId(int x, int y) const
{
	return entities.at(getTileOnPosition(x, y).getEntityOnTileId())->getTeamId();
}

int Board::getEntityOnTileTeamId(const Vector2i & position) const
{
	return entities.at(getTileOnPosition(position).getEntityOnTileId())->getTeamId();
}

BoardEntityType Board::getEntityOnTileType(int x, int y) const
{
	return entities.at(getTileOnPosition(x, y).getEntityOnTileId())->getEntityType();
}

BoardEntityType Board::getEntityOnTileType(const Vector2i & position) const
{
	return entities.at(getTileOnPosition(position).getEntityOnTileId())->getEntityType();
}

const Tile & Board::getTileOnPosition(const Vector2i & position) const
{
	return getTileOnPosition(position.x, position.y);
}

bool Board::isPositionOnBoard(int x, int y) const
{
	return x >= 0 && x < size.x && y >= 0 && y < size.y;
}

bool Board::isPositionOnBoard(Vector2i position) const
{
	return isPositionOnBoard(position.x, position.y);
}

void Board::initTiles() {
	tiles = std::vector<Tile>();
	tiles.reserve(size.x * size.y);
	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
			tiles.push_back(Tile(Vector2i(x, y)));
}

std::vector<int> Board::getIdsOfDeadEntities() const
{
	std::vector<int> ids;
	for (auto entity : entities)
		if (entity.second->isDead())
			ids.push_back(entity.first);
	return ids;
}

void Board::removeDeadEntities() {
	for (auto id : getIdsOfDeadEntities())
		entities.erase(id);
}

void Board::initTilesVertexes(const std::vector<Tile> tiles)
{
	tilesVertexes.setPrimitiveType(sf::Quads);
	for (auto tile : tiles)
		appendVertexesFromTile(tile);
}

void Board::appendVertexesFromTile(Tile &tile)
{
	auto vertexes = tile.getQuadVertexArray();
	for (int i = 0; i < vertexes.getVertexCount(); i++)
		tilesVertexes.append(vertexes[i]);
}

sf::IntRect Board::getVisibleRectangleOfTiles(const sf::RenderTarget& target) const
{
	auto tilesToDraw = createVisibleRectangleOfTiles(target);
	trimVisibleRectangeOfTiles(tilesToDraw);
	return tilesToDraw;
}

sf::IntRect Board::createVisibleRectangleOfTiles(const sf::RenderTarget & target) const
{
	auto viewSize = target.getView().getSize();
	auto center = target.getView().getCenter();
	return sf::IntRect((int)((center.x - viewSize.x / 2.f) / VisualizationParams::tileSizeInPx) - 1,
		(int)((center.y - viewSize.y / 2.f) / VisualizationParams::tileSizeInPx) - 1,
		(int)(viewSize.x / VisualizationParams::tileSizeInPx) + 2,
		(int)(viewSize.y / VisualizationParams::tileSizeInPx) + 2);
}

void Board::trimVisibleRectangeOfTiles(sf::IntRect & rectangleToTrim) const
{
	rectangleToTrim.left = RangeCalculator::trim(rectangleToTrim.left).toBeGreaterOrEqualThan(0);
	rectangleToTrim.top = RangeCalculator::trim(rectangleToTrim.top).toBeGreaterOrEqualThan(0);
	rectangleToTrim.width = RangeCalculator::trim(rectangleToTrim.width).toBeLessOrEqualThan(size.x - rectangleToTrim.left);
	rectangleToTrim.height = RangeCalculator::trim(rectangleToTrim.height).toBeLessOrEqualThan(size.y - rectangleToTrim.top);
}

void Board::updateColorsOfVisibleTiles(sf::RenderTarget & target)
{
	auto tilesToDraw = getVisibleRectangleOfTiles(target);
	for (int x = tilesToDraw.left; x < tilesToDraw.left + tilesToDraw.width; x++)
		for (int y = tilesToDraw.top; y < tilesToDraw.top + tilesToDraw.height; y++)
			updateVertexesColorForTile(x, y);
}

void Board::updateVertexesColorForTile(int x, int y)
{
	int tileIndex = positionToIndexInTiles(x, y);
	if (!tiles[tileIndex].content.hasNonZeroSignals() && tilesVertexes[tileIndex * 4].color == sf::Color::Black)
		return;
	auto tileColor = tiles[tileIndex].getCurrentColor();
	for (int i = 0; i < 4; i++)
		tilesVertexes[tileIndex * 4 + i].color = tileColor;
}

void Board::drawOn(sf::RenderTarget & target)
{
	updateColorsOfVisibleTiles(target);
	target.draw(tilesVertexes);
	for (auto entity : entities)
		entity.second->drawOn(target);
}

void Board::addEntity(std::shared_ptr<BoardEntity> newEntity) {
	entities[newEntity->getId()] = newEntity;
}

int Board::getNextAvailableId()
{
	lastUsedId++;
	return lastUsedId;
}

Vector2i Board::getSize() const
{
	return size;
}
