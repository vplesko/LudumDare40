#pragma once

#include "SFML/Graphics.hpp"
#include "SoldierManager.h"
#include <vector>
#include <memory>
#include "EnemyManager.h"
#include "BulletManager.h"
#include "TileMap.h"
#include "Background.h"

class StateInGame;

class World : public sf::Drawable, public sf::Transformable {
	StateInGame *state;

	std::shared_ptr<Background> background;
	std::shared_ptr<SoldierManager> soldiers;
	std::shared_ptr<EnemyManager> enemies;
	std::shared_ptr<BulletManager> bullets;
	std::shared_ptr<TileMap> tileMap;

public:
	World(StateInGame *state);

	void readLevel(std::string filename);

	StateInGame* getState() { return state; }

	SoldierManager* getSoldiers() { return soldiers.get(); }
	EnemyManager* getEnemies() { return enemies.get(); }
	BulletManager* getBullets() { return bullets.get(); }
	TileMap* getTileMap() { return tileMap.get(); }

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};