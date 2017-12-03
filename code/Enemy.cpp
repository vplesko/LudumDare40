#include "Enemy.h"
#include "World.h"
#include "Consts.h"
#include "MathUtility.hpp"
#include "Soldier.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "StateInGame.h"
#include "Tiled.h"

Enemy::Enemy(EnemyManager *manager) {
	this->manager = manager;

	hp = Consts::ENEMY_HP;
	speed = Consts::ENEMY_SPEED;
	dmg = Consts::ENEMY_DMG;
	attackCd = Consts::ENEMY_ATTACK_CD;
	attackCnt = 0;

	rangeSqr = Consts::ENEMY_BULLET_RANGE * Consts::ENEMY_BULLET_SPEED * 1.5f;
	rangeSqr = rangeSqr * rangeSqr;
	
	sprite.setTexture(manager->getWorld()->getState()->getEngine()->getTextures().get(Consts::ENEMY_TEXTURE));

	deathSound.setBuffer(manager->getWorld()->getState()->getEngine()->getSoundBuffers().get(Consts::KILL_SOUND));
}

sf::Vector2f Enemy::getCenter() const {
	return getPosition() + 
		sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

bool Enemy::contains(float x, float y) {
	sf::FloatRect bounds;
	bounds.left = getPosition().x;
	bounds.top = getPosition().y;
	bounds.width = sprite.getGlobalBounds().width;
	bounds.height = sprite.getGlobalBounds().height;
	return bounds.contains(x, y);
}

void Enemy::takeDmg(int amount) {
	if (hp > 0) {
		hp -= amount;
		if (isDead()) {
			deathSound.play();
		}
	}
}

void Enemy::onEvent(sf::Event ev) {
}

void Enemy::update(sf::Time delta) {
	if (attackCnt > 0) {
		attackCnt -= delta.asSeconds();
	}

	Soldier *soldier = manager->getWorld()->getSoldiers()->getNearestSoldier(getCenter());

	if (soldier && MathUtility::magnitudeSqr(soldier->getCenter() - getCenter()) <= rangeSqr) {
		if (attackCnt <= 0) {
			manager->getWorld()->getBullets()->createBullet(this, soldier->getCenter());
			attackCnt = attackCd;
		} else {
			sf::Vector2f oldPos = getPosition();
			sf::Vector2f movement = speed * delta.asSeconds() * MathUtility::normalize(soldier->getCenter() - getCenter());

			move(movement.x, 0);
			Tiled *tiled = manager->getWorld()->getTileMap()->getObjAtPos(getCenter());
			if ((tiled && !tiled->isDestroyed()) ||
				manager->getEnemyAt(getCenter()) != this) {
				setPosition(oldPos);
			}

			move(0, movement.y);
			tiled = manager->getWorld()->getTileMap()->getObjAtPos(getCenter());
			if ((tiled && !tiled->isDestroyed()) ||
				manager->getEnemyAt(getCenter()) != this) {
				setPosition(oldPos);
			}
		}
	}
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!isDead()) {
		states.transform *= getTransform();
		target.draw(sprite, states);
	}
}