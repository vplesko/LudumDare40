#include "Cage.h"
#include "TileMap.h"
#include "World.h"
#include "StateInGame.h"
#include "Consts.h"

Cage::Cage(TileMap *map) : Tiled(map) {
	hp = Consts::CAGE_HP;

	sprite.setTexture(map->getWorld()->getState()->getEngine()->getTextures().get(Consts::CAGE_TEXTURE));

	destroySound.setBuffer(map->getWorld()->getState()->getEngine()->getSoundBuffers().get(Consts::BREAK_SOUND));
}

void Cage::onHit() {
	if (!isDestroyed()) {
		--hp;
		if (isDestroyed()) {
			map->getWorld()->getSoldiers()->addSoldierAt(getPosition(), true);
			destroySound.play();
		}
	}
}

void Cage::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}