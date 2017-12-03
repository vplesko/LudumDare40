#include "Door.h"
#include "TileMap.h"
#include "World.h"
#include "StateInGame.h"
#include "Consts.h"

Door::Door(TileMap *map) : Tiled(map) {
	dmgd = false;
	hp = Consts::DOOR_HP;

	sprite.setTexture(map->getWorld()->getState()->getEngine()->getTextures().get(Consts::DOOR_TEXTURE));

	destroySound.setBuffer(map->getWorld()->getState()->getEngine()->getSoundBuffers().get(Consts::BREAK_SOUND));
}

void Door::onHit() {
	if (!dmgd) {
		dmgd = true;
		sprite.setTexture(map->getWorld()->getState()->getEngine()->getTextures().get(Consts::DOOR_DMG_TEXTURE));
	}

	if (!isDestroyed()) {
		--hp;
		if (isDestroyed()) {
			destroySound.play();
		}
	}
}

void Door::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}