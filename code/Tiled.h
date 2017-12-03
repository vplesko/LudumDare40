#pragma once

#include "SFML/Graphics.hpp"

class TileMap;

class Tiled : public sf::Drawable, public sf::Transformable {
protected:
	TileMap *map;

	unsigned x, y;

public:
	Tiled(TileMap *map, unsigned x = 0, unsigned y = 0);

	int getX() const { return x; }
	void setX(int x) { this->x = x; }
	int getY() const { return y; }
	void setY(int y) { this->y = y; }

	virtual unsigned getW() const { return 1; }
	virtual unsigned getH() const { return 1; }

	sf::Vector2f getCenter() const;

	virtual bool isDestroyable() const { return false; }
	virtual bool isDestroyed() const { return false; }
	virtual void onHit() {}

	virtual void onEvent(sf::Event ev) {}
	virtual void update(sf::Time delta) {}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}

	virtual ~Tiled() {}
};