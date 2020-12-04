#pragma once
#include <SFML/Graphics.hpp>
#include <Utils/Types.hpp>

#include <AntsLib/Core/Board/BoardState/BoardEntity.hpp>
#include <AntsLib/Core/Board/BoardState/Tile.hpp>

class BoardEntity;
enum BoardEntityType;

class Board {
private:
	Vector2i size;
	std::vector<Tile> tiles;
	std::map<int, std::shared_ptr<BoardEntity>> entities;
	sf::VertexArray tilesVertexes;

	int lastUsedId = 0;

	void initTilesVertexes(const std::vector<Tile> tiles);
	void appendVertexesFromTile(Tile &tile);
	sf::IntRect getVisibleRectangleOfTiles(const sf::RenderTarget& target) const;
	sf::IntRect createVisibleRectangleOfTiles(const sf::RenderTarget& target) const;
	void trimVisibleRectangeOfTiles(sf::IntRect& rectangleToTrim) const;

	void updateColorsOfVisibleTiles(sf::RenderTarget & target);
	void updateVertexesColorForTile(int x, int y);

	int positionToIndexInTiles(int x, int y) const;

	void initTiles();

	std::vector<int> getIdsOfDeadEntities() const;
	void removeDeadEntities();
public:
	Board(Vector2i size);
	void perform1Cycle();
	void drawOn(sf::RenderTarget & target);
	void addEntity(std::shared_ptr<BoardEntity> newEntity);
	int getNextAvailableId();
	Vector2i getSize() const;

	Tile& getTileOnPosition(int x, int y);
	Tile& getTileOnPosition(const Vector2i& position);
	const Tile& getTileOnPosition(int x, int y) const;
	const Tile& getTileOnPosition(const Vector2i& position) const;
	int getEntityOnTileTeamId(int x, int y) const;
	int getEntityOnTileTeamId(const Vector2i& position) const;
	BoardEntityType getEntityOnTileType(int x, int y) const;
	BoardEntityType getEntityOnTileType(const Vector2i& position) const;
	bool isPositionOnBoard(int x, int y) const;
	bool isPositionOnBoard(Vector2i position) const;
};