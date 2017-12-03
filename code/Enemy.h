#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class EnemyManager;

class Enemy : public sf::Drawable, public sf::Transformable {
	EnemyManager *manager;

	sf::Sprite sprite;

	sf::Sound deathSound;

	int hp;
	float speed;
	int dmg;
	float attackCd, attackCnt;
	float rangeSqr;

public:
	Enemy(EnemyManager *manager);

	sf::Vector2f getCenter() const;

	bool contains(float x, float y);

	int getDmg() const { return dmg; }

	bool isDead() const { return hp <= 0; }	
	void takeDmg(int amount);

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};