#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Randomizer.hpp"
#include "StateMainMenu.h"

int main() {
	sf::ContextSettings settings;
	//settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(640, 480), "Crimson Assault", sf::Style::None, settings);
	window.setKeyRepeatEnabled(false);
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(120);
	window.setMouseCursorVisible(false);

	Randomizer::init();

	Engine engine(window);
	engine.changeState(new StateMainMenu(&engine));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else
				engine.onEvent(event);
		}

		engine.onTime();

		window.clear(engine.getClearColor());
		window.draw(engine);
		window.display();

		if (engine.isOver() && window.isOpen())
			window.close();
	}

	return 0;
}
