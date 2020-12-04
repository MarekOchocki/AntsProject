#pragma once
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <AntsLib/Core/Environment.hpp>
#include <AntsLib/Visualization/VisualizationParams.hpp>

class Simulation {
private:
	std::shared_ptr<Environment> environment;
	std::unique_ptr<sf::RenderWindow> window;
	sf::RenderTexture textureForImageSaving;
	sf::View currentView;
	bool isSimulationPaused = true;
	bool isVisualizationOn = true;
	int cycleCounter = 0;

	bool isLMBPressed = false;
	sf::Vector2f lastMousePos;

	void handleEvents();
	void visualizeEnvironment();
	void simulate1Cycle();

	void handleKeyPressedEvent(const sf::Event & event);
	void handleScrollEvent(const sf::Event & event);
	void handleWindowClosedEvent(const sf::Event & event);
	void handleMouseMoveEvent(const sf::Event & event);


public:
	Simulation(std::shared_ptr<Environment> & env);
	void start();
};