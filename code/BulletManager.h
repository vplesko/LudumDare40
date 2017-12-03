#pragma once

#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include <vector>
#include <memory>

class World;
class Soldier;
class Enemy;

class BulletManager : public sf::Drawable, public sf::Transformable {
	World *world;

	std::vector<std::shared_ptr<Bullet>> bullets;

	void removeToDestroyBullets();

public:
	BulletManager(World *world);

	World* getWorld() { return world; }

	void createBullet(Soldier *soldier, sf::Vector2f to);
	void createBullet(Enemy *enemy, sf::Vector2f to);

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};