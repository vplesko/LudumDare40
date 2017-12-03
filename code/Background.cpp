#include "Background.h"
#include "Consts.h"
#include "World.h"
#include "StateInGame.h"

Background::Background(World *world) {
	this->world = world;

	texture.loadFromFile(Consts::BACK_TEXTURE);
	texture.setRepeated(true);
	sprite.setTexture(texture);
	// lazy hack
	sprite.setTextureRect(sf::IntRect(0, 0, 1100 * (int)Consts::TILE_SIZE.x, 1100 * (int)Consts::TILE_SIZE.y));
	sprite.move(-100.f * Consts::TILE_SIZE);
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}