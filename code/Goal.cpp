#include "Goal.h"
#include "TileMap.h"
#include "World.h"
#include "StateInGame.h"
#include "Consts.h"

Goal::Goal(TileMap *map) : Tiled(map) {
	dmgd = false;
	hp = Consts::GOAL_HP;

	sprite.setTexture(map->getWorld()->getState()->getEngine()->getTextures().get(Consts::GOAL_TEXTURE));

	destroySound.setBuffer(map->getWorld()->getState()->getEngine()->getSoundBuffers().get(Consts::DESTROY_SOUND));
}

void Goal::onHit() {
	if (!dmgd) {
		dmgd = true;
		sprite.setTexture(map->getWorld()->getState()->getEngine()->getTextures().get(Consts::GOAL_DMG_TEXTURE));
	}

	if (!isDestroyed()) {
		--hp;
		if (isDestroyed()) {
			map->onGoalDestroyed();
			destroySound.play();
		}
	}
}

void Goal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}