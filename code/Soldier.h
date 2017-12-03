#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class SoldierManager;
class Enemy;
class Tiled;

class Soldier : public sf::Drawable, public sf::Transformable {
	SoldierManager *manager;
	
	sf::Sprite sprite;
	sf::RectangleShape outline;

	sf::Sound shootSound;

	int hp;
	float speed;
	int dmg;
	float attackCd, attackCnt;

	bool drawOutline;

	bool hasOrder;
	Enemy *targetAttack;
	Tiled *targetDestroy;
	sf::Vector2f targetMove;

public:
	Soldier(SoldierManager *manager);

	sf::Vector2f getCenter() const;

	bool contains(float x, float y);

	void setSpeed(float f) { speed = f; }
	void setAttackCd(float f) { attackCd = f; attackCnt = 0; }
	int getDmg() const { return dmg; }

	bool isDead() const { return hp <= 0; }
	void takeDmg(int amount);

	void giveOrderMove(float x, float y);
	void giveOrderAttack(Enemy *enemy);
	void giveOrderDestroy(Tiled *tiled);
	void cancelOrders() { hasOrder = false; }

	void setDrawOutline(bool b);

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};