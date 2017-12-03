#pragma once

#include "SFML/Graphics.hpp"
#include "Enemy.h"
#include <vector>
#include <memory>

class World;

class EnemyManager : public sf::Drawable, public sf::Transformable {
	World *world;

	std::vector<std::shared_ptr<Enemy>> enemies;

public:
	EnemyManager(World *world);

	World* getWorld() { return world; }

	void readAddEnemies(std::ifstream &in);

	// TODO: optimize search
	Enemy* getEnemyAt(float x, float y);
	Enemy* getEnemyAt(sf::Vector2f v) { return getEnemyAt(v.x, v.y); }

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};