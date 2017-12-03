#pragma once

#include "SFML/Graphics.hpp"
#include "Soldier.h"
#include <vector>
#include <memory>

class World;

class SoldierManager : public sf::Drawable, public sf::Transformable {
	World *world;

	unsigned liveSoldierCnt;

	std::vector<std::shared_ptr<Soldier>> soldiers;

	void recalcSoldierSpeed();
	void recalcSoldierAttackCd();

public:
	SoldierManager(World *world);

	World* getWorld() { return world; }

	void readAddSoldiers(std::ifstream &in);

	void addSoldierAt(float x, float y, bool recalcStats);
	void addSoldierAt(sf::Vector2f v, bool recalcStats) { addSoldierAt(v.x, v.y, recalcStats); }

	unsigned getLiveSoldierCnt() const { return liveSoldierCnt; }
	Soldier* getALivingSoldier();
	Soldier* getNearestSoldier(sf::Vector2f v);
	void onSoldierDied(Soldier *soldier);

	// TODO: optimize search
	Soldier* getSoldierAt(float x, float y);
	Soldier* getSoldierAt(sf::Vector2f v) { return getSoldierAt(v.x, v.y); }
	
	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};