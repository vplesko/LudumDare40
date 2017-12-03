#pragma once

#include "GameState.hpp"

class StateMainMenu : public GameState {
	sf::Sprite screen;

public:
	StateMainMenu(Engine *engine);

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};