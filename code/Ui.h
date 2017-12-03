#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include "Cursor.h"

class StateInGame;

class Ui : public sf::Drawable, public sf::Transformable {
	StateInGame *state;

	std::shared_ptr<Cursor> cursor;

public:
	Ui(StateInGame *state);

	StateInGame* getState() { return state; }

	Cursor* getCursor() { return cursor.get(); }

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};