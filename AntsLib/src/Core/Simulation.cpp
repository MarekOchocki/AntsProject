#include <AntsLib/Core/Simulation.hpp>
#include <AntsLib/Core/Settings.hpp>

void Simulation::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleKeyPressedEvent(event);
		handleMouseMoveEvent(event);
		handleScrollEvent(event);
		handleWindowClosedEvent(event);
	}
}

void Simulation::visualizeEnvironment()
{
	window->clear(VisualizationParams::backgroundColor);
	environment->drawOn(*window);
	window->display();
}

void Simulation::simulate1Cycle()
{
	if (!isSimulationPaused) {
		environment->perform1Cycle();
		cycleCounter++;
	}

	if (isVisualizationOn)
		visualizeEnvironment();
	handleEvents();
}

void Simulation::handleKeyPressedEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return;
	if(event.key.code == sf::Keyboard::V)
		isVisualizationOn = !isVisualizationOn;
	if (event.key.code == sf::Keyboard::P)
		isSimulationPaused = !isSimulationPaused;
	if (event.key.code == sf::Keyboard::O)
		Settings::outputLogs = !Settings::outputLogs;
}

void Simulation::handleScrollEvent(const sf::Event & event)
{
	if (event.type != sf::Event::MouseWheelScrolled)
		return;
	float scale = pow(1.1f, -event.mouseWheelScroll.delta);
	currentView.zoom(scale);
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	sf::Vector2f fromCenterToMousePos = mousePos - currentView.getCenter();
	sf::Vector2f scaledFromCenterToMousePos = fromCenterToMousePos * scale;
	currentView.move(fromCenterToMousePos - scaledFromCenterToMousePos);
	window->setView(currentView);
}

void Simulation::handleWindowClosedEvent(const sf::Event & event)
{
	if (event.type != sf::Event::Closed)
		return;
	window->close();
}

void Simulation::handleMouseMoveEvent(const sf::Event & event)
{
	if (event.type != sf::Event::MouseMoved)
		return;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		sf::Vector2f transition = lastMousePos - mousePos;
		currentView.move(transition);
		window->setView(currentView);
	}
	lastMousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

Simulation::Simulation(std::shared_ptr<Environment> & env)
{
	environment = env;
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 1000), "Ants Project", sf::Style::Default);
	currentView = sf::View(sf::Vector2f(2000, 2000), sf::Vector2f(4000, 4000));
	window->setView(currentView);
	textureForImageSaving.create(window->getSize().x * 2, window->getSize().y * 2);
	textureForImageSaving.setView(window->getView());
}

void Simulation::start()
{
	while (window->isOpen())
	{
		simulate1Cycle();
	}
}
