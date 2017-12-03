#include "Ui.h"
#include "StateInGame.h"

Ui::Ui(StateInGame *state) {
	this->state = state;

	cursor = std::make_shared<Cursor>(this);
}

void Ui::onEvent(sf::Event ev) {
}

void Ui::update(sf::Time delta) {
	cursor->update(delta);
}

void Ui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	cursor->draw(target, states);
}