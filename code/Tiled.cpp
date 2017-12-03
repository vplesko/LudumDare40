#include "Tiled.h"
#include "TileMap.h"
#include "Consts.h"

Tiled::Tiled(TileMap *map, unsigned x, unsigned y) {
	this->map = map;
	this->x = x;
	this->y = y;
}

sf::Vector2f Tiled::getCenter() const {
	return sf::Vector2f(Consts::TILE_SIZE.x * (x + getW() / 2.f), Consts::TILE_SIZE.y * (y + getH() / 2.f));
}