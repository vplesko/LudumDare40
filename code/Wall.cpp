#include "Wall.h"
#include "TileMap.h"
#include "World.h"
#include "StateInGame.h"
#include "Consts.h"

Wall::Wall(TileMap *map) : Tiled(map) {
	sprite.setTexture(map->getWorld()->getState()->getEngine()->getTextures().get(Consts::WALL_TEXTURE));
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}