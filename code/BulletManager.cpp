#include "BulletManager.h"
#include "World.h"
#include "Soldier.h"
#include "Enemy.h"
#include "Consts.h"
#include "MathUtility.hpp"

BulletManager::BulletManager(World *world) {
	this->world = world;
}

void BulletManager::createBullet(Soldier *soldier, sf::Vector2f to) {
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this);
	bullet->setPosition(soldier->getCenter());
	bullet->setDirection(MathUtility::normalize(to - soldier->getCenter()));
	bullet->setFriendly(true);
	bullet->setDmg(soldier->getDmg());
	bullet->setSpeed(Consts::SOLDIER_BULLET_SPEED);
	bullet->setRange(Consts::SOLDIER_BULLET_RANGE);
	bullet->setColor(Consts::SOLDIER_BULLET_COL);

	bullets.push_back(bullet);
}

void BulletManager::createBullet(Enemy *enemy, sf::Vector2f to) {
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this);
	bullet->setPosition(enemy->getCenter());
	bullet->setDirection(MathUtility::normalize(to - enemy->getCenter()));
	bullet->setFriendly(false);
	bullet->setDmg(enemy->getDmg());
	bullet->setSpeed(Consts::ENEMY_BULLET_SPEED);
	bullet->setRange(Consts::ENEMY_BULLET_RANGE);
	bullet->setColor(Consts::ENEMY_BULLET_COL);

	bullets.push_back(bullet);
}

void BulletManager::onEvent(sf::Event ev) {
	for (auto it : bullets) {
		it.get()->onEvent(ev);
	}
}

void BulletManager::removeToDestroyBullets() {
	std::size_t i = 0, j = 0;
	while (j < bullets.size()) {
		if (!bullets[j]->isToDestroy()) {
			bullets[i] = bullets[j];
			++i;
		} else {
			bullets[j].reset();
		}

		++j;
	}

	bullets.resize(i);
}

void BulletManager::update(sf::Time delta) {
	for (auto it : bullets) {
		it.get()->update(delta);
	}

	removeToDestroyBullets();
}

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto it : bullets) {
		it.get()->draw(target, states);
	}
}