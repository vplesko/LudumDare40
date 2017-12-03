#pragma once

#include "GameState.hpp"
#include "Ui.h"
#include "World.h"
#include <memory>
#include "MidLevelInfo.h"

class StateInGame : public GameState {
	MidLevelInfo *info;

	std::shared_ptr<Ui> ui;
	std::shared_ptr<World> world;

public:
	StateInGame(Engine *engine, MidLevelInfo *info = 0);

	MidLevelInfo* getInfo() { return info; }
	World* getWorld() { return world.get(); }
	Ui* getUi() { return ui.get(); }

	void onSoldierDied();

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};