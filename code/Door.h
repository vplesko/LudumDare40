#pragma once

#include "Tiled.h"
#include "SFML/Audio.hpp"

class Door : public Tiled {
	sf::Sprite sprite;

	sf::Sound destroySound;

	bool dmgd;
	int hp;

public:
	Door(TileMap *map);

	bool isDestroyable() const { return true; }
	bool isDestroyed() const { return hp <= 0; }
	void onHit();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};