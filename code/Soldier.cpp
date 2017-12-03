#include "Soldier.h"
#include "SoldierManager.h"
#include "Consts.h"
#include "MathUtility.hpp"
#include "Enemy.h"
#include "World.h"
#include "BulletManager.h"
#include "StateInGame.h"
#include "TileMap.h"
#include "Tiled.h"

Soldier::Soldier(SoldierManager *manager) {
	this->manager = manager;
	
	sprite.setTexture(manager->getWorld()->getState()->getEngine()->getTextures().get(Consts::SOLDIER_TEXTURE));

	shootSound.setBuffer(manager->getWorld()->getState()->getEngine()->getSoundBuffers().get(Consts::SHOOT_SOUND));

	hp = Consts::SOLDIER_HP;
	speed = 0;
	dmg = Consts::SOLDIER_DMG;
	attackCd = 0;
	attackCnt = 0;

	outline = sf::RectangleShape(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineColor(sf::Color::Yellow);
	outline.setOutlineThickness(-1.f);

	drawOutline = false;
	hasOrder = false;
	targetAttack = 0;
	targetDestroy = 0;
}

sf::Vector2f Soldier::getCenter() const {
	return getPosition() + 
		sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

bool Soldier::contains(float x, float y) {
	sf::FloatRect bounds;
	bounds.left = getPosition().x;
	bounds.top = getPosition().y;
	bounds.width = sprite.getGlobalBounds().width;
	bounds.height = sprite.getGlobalBounds().height;
	return bounds.contains(x, y);
}

void Soldier::takeDmg(int amount) {
	if (hp > 0) {
		hp -= amount;
		if (isDead()) manager->onSoldierDied(this);
	}
}

void Soldier::setDrawOutline(bool b) {
	drawOutline = b;
}

void Soldier::giveOrderMove(float x, float y) {
	hasOrder = true;
	targetAttack = 0;
	targetDestroy = 0;
	this->targetMove = sf::Vector2f(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}

void Soldier::giveOrderAttack(Enemy *enemy) {
	targetAttack = enemy;
	hasOrder = enemy != 0;
}

void Soldier::giveOrderDestroy(Tiled *tiled) {
	targetAttack = 0;
	targetDestroy = tiled;
	hasOrder = tiled != 0;
}

void Soldier::onEvent(sf::Event ev) {
}

void Soldier::update(sf::Time delta) {
	if (attackCnt > 0) {
		attackCnt -= delta.asSeconds();
	}

	if (hasOrder) {
		if (targetAttack != 0) {
			if (!targetAttack->isDead()) {
				if (attackCnt <= 0) {
					manager->getWorld()->getBullets()->createBullet(this, targetAttack->getCenter());
					shootSound.play();

					attackCnt = attackCd;
				}
			}

			if (targetAttack->isDead()) {
				targetAttack = 0;
				hasOrder = false;
			}
		} else if (targetDestroy != 0) {
			if (!targetDestroy->isDestroyed()) {
				if (attackCnt <= 0) {
					manager->getWorld()->getBullets()->createBullet(this, targetDestroy->getCenter());
					shootSound.play();
					
					attackCnt = attackCd;
				}
			}

			if (targetDestroy->isDestroyed()) {
				targetDestroy = 0;
				hasOrder = false;
			}
		} else {
			sf::Vector2f oldPos = getPosition();
			sf::Vector2f direction = targetMove - oldPos;
			float movement = speed * delta.asSeconds();
			
			if (MathUtility::magnitudeSqr(direction) <= movement * movement) {
				setPosition(targetMove);
				hasOrder = false;
			} else {
				move(movement * MathUtility::normalize(direction));
			}

			Tiled *tiled = manager->getWorld()->getTileMap()->getObjAtPos(getCenter());
			if ((tiled && !tiled->isDestroyed()) ||
				manager->getSoldierAt(getCenter()) != this) {
				setPosition(oldPos);
			}
		}
	}
}

void Soldier::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
	if (drawOutline) target.draw(outline, states);
}