#include "Cursor.h"
#include "Ui.h"
#include "StateInGame.h"
#include "Consts.h"
#include "Enemy.h"
#include "Tiled.h"

Cursor::Cursor(Ui *ui) {
	this->ui = ui;
	setShowCrosshair(false);
}

void Cursor::setShowCrosshair(bool b) {
	crosshair = b;
	if (crosshair) {
		sprite.setTexture(ui->getState()->getEngine()->getTextures().get(Consts::CROSSHAIR_TEXTURE));
		sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
	} else {
		sprite.setTexture(ui->getState()->getEngine()->getTextures().get(Consts::CURSOR_TEXTURE));
		sprite.setOrigin(0, 0);
	}
}

sf::Vector2f Cursor::getWorldPosition() const {
	return ui->getState()->getWorld()->getInverseTransform().transformPoint(getPosition());
}

void Cursor::update(sf::Time delta) {
	setPosition(sf::Vector2f(sf::Mouse::getPosition(ui->getState()->getEngine()->getWindow())));

	sf::Vector2f pos = getWorldPosition();

	Enemy *enemy = ui->getState()->getWorld()->getEnemies()->getEnemyAt(pos);
	if (enemy && !enemy->isDead()) {
		setShowCrosshair(true);
		return;
	}

	Tiled *tiled = ui->getState()->getWorld()->getTileMap()->getObjAtPos(pos);
	if (tiled && !tiled->isDestroyed()) {
		setShowCrosshair(true);
		return;
	}

	setShowCrosshair(false);
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}