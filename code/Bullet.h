#pragma once

#include "SFML/Graphics.hpp"

class BulletManager;

class Bullet : public sf::Drawable, public sf::Transformable {
	BulletManager *manager;

	bool friendly;
	int dmg;
	float speed;
	float range, passed;
	sf::Vector2f direction;

	bool toDestroy;

	sf::RectangleShape rect;

public:
	Bullet(BulletManager *manager);

	void setFriendly(bool b) { friendly = b; }
	void setDmg(int i) { dmg = i; }
	void setSpeed(float f) { speed = f; }
	void setRange(float f) { range = f * f; }
	void setDirection(sf::Vector2f v) { direction = v; }

	void setColor(sf::Color c) { rect.setFillColor(c); }

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isToDestroy() const { return toDestroy; }
};