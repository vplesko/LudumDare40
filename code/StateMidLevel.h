#pragma once

#include "GameState.hpp"
#include "MidLevelInfo.h"
#include <vector>

class StateMidLevel : public GameState {
	MidLevelInfo *info;

	sf::Text text;

	std::vector<sf::Sprite> sprites;

public:
	StateMidLevel(Engine *engine, MidLevelInfo *info);

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};