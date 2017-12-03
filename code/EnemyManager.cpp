#include "EnemyManager.h"
#include "World.h"
#include <fstream>

EnemyManager::EnemyManager(World *world) {
	this->world = world;
}

void EnemyManager::readAddEnemies(std::ifstream &in) {
	unsigned cnt;
	float x, y;
	in >> cnt;

	for (unsigned i = 0; i < cnt; ++i) {
		in >> x >> y;

		enemies.push_back(std::make_shared<Enemy>(this));
		enemies[enemies.size() - 1]->setPosition(x, y);
	}

	if (cnt == 0) {
		std::string dummy;
		std::getline(in, dummy);
	}
}

Enemy* EnemyManager::getEnemyAt(float x, float y) {
	for (auto it : enemies) {
		if (!it->isDead() && it->contains(x, y)) {
			return it.get();
		}
	}

	return 0;
}

void EnemyManager::onEvent(sf::Event ev) {
	for (auto it : enemies) {
		if (!it->isDead())
			it->onEvent(ev);
	}
}

void EnemyManager::update(sf::Time delta) {
	for (auto it : enemies) {
		if (!it.get()->isDead())
			it.get()->update(delta);
	}
}

void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto it : enemies) {
		if (!it.get()->isDead())
			it.get()->draw(target, states);
	}
}