#pragma once
#include <vector>

#include <Utils/Types.hpp>

class GeometryCalculator {
private:
	static const std::vector<Vector2f> degreesToNormalizedVector;

	static int degreesToBase360(int degrees);

public:
	static int getManhattanDistance(const Vector2i& firstVector, const Vector2i& secondVector);
	static Vector2f angleToNormalizedVector(int degrees);
	static Vector2f normalizeVector(const Vector2f & vector);
	static float getNormOfVector(const Vector2f & vector);
	static std::vector<Vector2i> getDirectionsToEveryAdjacentTileClockwise(int startingRotationInDegrees);
	static Vector2i getDirectionToAdjacentTile(int rotationInDegrees);
};