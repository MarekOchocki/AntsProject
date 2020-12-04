#include <AntsLib/Core/Board/BoardState/Tile.hpp>

void Tile::blendWithCurrentColor(const sf::Color & toBlend)
{
	currentColor.r = ((255 - toBlend.a) * currentColor.r + toBlend.a * toBlend.r) / 255;
	currentColor.g = ((255 - toBlend.a) * currentColor.g + toBlend.a * toBlend.g) / 255;
	currentColor.b = ((255 - toBlend.a) * currentColor.b + toBlend.a * toBlend.b) / 255;
}

sf::Color Tile::getFoodOnGroundColor() const
{
	sf::Color foodColor = sf::Color::White;
	foodColor.a = content.getValue(GroundContent::FOOD) * 255.f;
	return foodColor;
}

sf::Color Tile::getCurrentColor()
{
	currentColor = VisualizationParams::boardBackgroundColor;
	blendWithCurrentColor(getFoodOnGroundColor());
	return currentColor;
}

Tile::Tile(Vector2i position)
{
	this->position = position;
}

Vector2i Tile::getPosition() const
{
	return position;
}

int Tile::getEntityOnTileId() const
{
	return hasEntity ? entityOnTileId : -1;
}

void Tile::setEntityOnTileId(int id)
{
	hasEntity = true;
	entityOnTileId = id;
}

void Tile::unsetEntityOnTileId()
{
	hasEntity = false;
}

bool Tile::isEntityOnTile() const
{
	return hasEntity;
}

sf::VertexArray Tile::getQuadVertexArray()
{
	auto result = sf::VertexArray();
	auto color = getCurrentColor();
	result.append(sf::Vertex(sf::Vector2f((position.x) * VisualizationParams::tileSizeInPx, (position.y) * VisualizationParams::tileSizeInPx), color));
	result.append(sf::Vertex(sf::Vector2f((position.x) * VisualizationParams::tileSizeInPx, (position.y + 1) * VisualizationParams::tileSizeInPx), color));
	result.append(sf::Vertex(sf::Vector2f((position.x + 1) * VisualizationParams::tileSizeInPx, (position.y + 1) * VisualizationParams::tileSizeInPx), color));
	result.append(sf::Vertex(sf::Vector2f((position.x + 1) * VisualizationParams::tileSizeInPx, (position.y + 0) * VisualizationParams::tileSizeInPx), color));
	return result;
}
