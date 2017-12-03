#include "StateMainMenu.h"
#include "Consts.h"
#include "StateInGame.h"

StateMainMenu::StateMainMenu(Engine *engine) : GameState(engine) {
	engine->setClearColor(sf::Color::Black);

	screen.setTexture(getEngine()->getTextures().get(Consts::MAIN_MENU_SCREEN));
}

void StateMainMenu::onEvent(sf::Event ev) {
	if (ev.type == sf::Event::KeyPressed) {
		if (ev.key.code == sf::Keyboard::Escape) {
			getEngine()->setOver(true);
			return;
		} else {
			getEngine()->changeState(new StateInGame(getEngine()));
			return;
		}
	}
}

void StateMainMenu::update(sf::Time delta) {
}

void StateMainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(screen, states);
}