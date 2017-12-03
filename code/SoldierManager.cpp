#include "SoldierManager.h"
#include "World.h"
#include "MathUtility.hpp"
#include <fstream>
#include "Consts.h"
#include "TileMap.h"
#include "Tiled.h"
#include "StateInGame.h"

SoldierManager::SoldierManager(World *world) {
	this->world = world;

	liveSoldierCnt = 0;
}

void SoldierManager::readAddSoldiers(std::ifstream &in) {
	unsigned cnt;
	float x, y;
	in >> cnt;

	for (unsigned i = 0; i < cnt; ++i) {
		in >> x >> y;
		addSoldierAt(x, y, false);
	}
	
	recalcSoldierSpeed();
	recalcSoldierAttackCd();
}

void SoldierManager::addSoldierAt(float x, float y, bool recalcStats) {
	soldiers.push_back(std::make_shared<Soldier>(this));
	soldiers[soldiers.size() - 1]->setPosition(x, y);
	++liveSoldierCnt;

	if (recalcStats) {
		recalcSoldierSpeed();
		recalcSoldierAttackCd();
	}
}

void SoldierManager::recalcSoldierSpeed() {
	if (liveSoldierCnt == 0) return;

	float speed = Consts::calcSoldierSpeed(liveSoldierCnt);

	for (auto it : soldiers)
		it->setSpeed(speed);
}

void SoldierManager::recalcSoldierAttackCd() {
	if (liveSoldierCnt == 0) return;

	float attackCd = Consts::calcSoldierAttackCd(liveSoldierCnt);

	for (auto it : soldiers)
		it->setAttackCd(attackCd);
}

void SoldierManager::onSoldierDied(Soldier *soldier) {
	--liveSoldierCnt;
	recalcSoldierSpeed();
	recalcSoldierAttackCd();

	getWorld()->getState()->onSoldierDied();
}

Soldier* SoldierManager::getALivingSoldier() {
	for (auto it : soldiers)
		if (!it->isDead())
			return it.get();

	return 0;
}

Soldier* SoldierManager::getNearestSoldier(sf::Vector2f v) {
	if (soldiers.empty()) return 0;

	float distSqr = -1;
	unsigned ind;
	for (unsigned i = 0; i < soldiers.size(); ++i) {
		if (soldiers[i]->isDead())
			continue;

		float currSqr = MathUtility::magnitudeSqr(v - soldiers[i]->getCenter());
		if (distSqr < 0 || distSqr > currSqr) {
			distSqr = currSqr;
			ind = i;
		}
	}

	if (distSqr < 0) return 0;
	else return soldiers[ind].get();
}

Soldier* SoldierManager::getSoldierAt(float x, float y) {
	for (auto it : soldiers) {
		if (!it->isDead() && it->contains(x, y)) {
			return it.get();
		}
	}

	return 0;
}

void SoldierManager::onEvent(sf::Event ev) {
	if (ev.type == sf::Event::MouseButtonReleased) {
		if (ev.mouseButton.button == sf::Mouse::Right) {
			Enemy *enemy = world->getEnemies()->getEnemyAt((float)ev.mouseButton.x, (float)ev.mouseButton.y);
			if (enemy) {
				for (auto it : soldiers)
					it->giveOrderAttack(enemy);
			} else {
				Tiled *tiled = world->getTileMap()->getObjAtPos(sf::Vector2f((float)ev.mouseButton.x, (float)ev.mouseButton.y));
				if (tiled && !tiled->isDestroyed() && tiled->isDestroyable()) {
					for (auto it : soldiers)
						it->giveOrderDestroy(tiled);
				} else {
					for (auto it : soldiers)
						it->giveOrderMove((float)ev.mouseButton.x, (float)ev.mouseButton.y);
				}
			}
		}
	} else if (ev.type == sf::Event::KeyPressed) {
		if (ev.key.code == sf::Keyboard::Space) {
			for (auto it : soldiers)
				it->cancelOrders();
		}
	}
}

void SoldierManager::update(sf::Time delta) {
	for (auto it : soldiers) {
		if (!it->isDead())
			it.get()->update(delta);
	}
}

void SoldierManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto it : soldiers) {
		if (!it->isDead())
			it.get()->draw(target, states);
	}
}