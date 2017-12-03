#pragma once

#include "Tiled.h"

class Wall : public Tiled {
	sf::Sprite sprite;

public:
	Wall(TileMap *map);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};