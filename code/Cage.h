#pragma once

#include "Tiled.h"
#include "SFML/Audio.hpp"

class Cage : public Tiled {
	sf::Sprite sprite;

	sf::Sound destroySound;

	int hp;

public:
	Cage(TileMap *map);

	bool isDestroyable() const { return true; }
	bool isDestroyed() const { return hp <= 0; }
	void onHit();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};