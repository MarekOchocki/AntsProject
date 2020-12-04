#pragma once
#include <SFML/Graphics.hpp>

class Environment {
public:
	virtual void perform1Cycle() = 0;
	virtual void drawOn(sf::RenderTarget & target) = 0;
};