#include "Bullet.h"
#include "BulletManager.h"
#include "Consts.h"
#include "World.h"
#include "SoldierManager.h"
#include "EnemyManager.h"
#include "MathUtility.hpp"
#include "TileMap.h"
#include "Tiled.h"

Bullet::Bullet(BulletManager *manager) {
	this->manager = manager;

	rect.setSize(Consts::BULLET_SIZE);
	rect.setOrigin(Consts::BULLET_SIZE.x / 2, Consts::BULLET_SIZE.y / 2);

	toDestroy = false;
	passed = range = 0;
}

void Bullet::onEvent(sf::Event ev) {
}

void Bullet::update(sf::Time delta) {
	move(direction * speed * delta.asSeconds());

	if (friendly) {
		Enemy *enemy = manager->getWorld()->getEnemies()->getEnemyAt(getPosition());
		if (enemy) {
			enemy->takeDmg(dmg);
			toDestroy = true;
			return;
		}
	} else {
		Soldier *soldier = manager->getWorld()->getSoldiers()->getSoldierAt(getPosition());
		if (soldier) {
			soldier->takeDmg(dmg);
			toDestroy = true;
			return;
		}
	}

	Tiled *tiledObj = manager->getWorld()->getTileMap()->getObjAtPos(getPosition());
	if (tiledObj && !tiledObj->isDestroyed()) {
		if (friendly)
			tiledObj->onHit();
		toDestroy = true;
		return;
	}

	passed += delta.asSeconds();
	if (passed >= range) {
		toDestroy = true;
		return;
	}
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(rect, states);
}