#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include <Utils/Types/Vector2i.hpp>
#include <Utils/Generators.hpp>

#include <AntsLib/Core/Board/BoardState/GroundContent.hpp>
#include <AntsLib/Visualization/VisualizationParams.hpp>

class Tile {
private:
	Vector2i position;
	bool hasEntity = false;
	int entityOnTileId = 0;

	sf::Color currentColor;
	void blendWithCurrentColor(const sf::Color & toBlend);
	sf::Color getFoodOnGroundColor() const;
public:
	GroundContent content;

	Tile(Vector2i position);
	Vector2i getPosition() const;
	int getEntityOnTileId() const;
	void setEntityOnTileId(int id);
	void unsetEntityOnTileId();
	bool isEntityOnTile() const;

	sf::VertexArray getQuadVertexArray();
	sf::Color getCurrentColor();
};