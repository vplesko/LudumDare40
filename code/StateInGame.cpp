#include "StateInGame.h"
#include "Consts.h"
#include "StateMidLevel.h"
#include "SoldierManager.h"
#include "StateMainMenu.h"

StateInGame::StateInGame(Engine *engine, MidLevelInfo *info) : GameState(engine) {
	if (info != 0) {
		this->info = info;
	} else {
		this->info = new MidLevelInfo();
	}

	ui = std::make_shared<Ui>(this);
	world = std::make_shared<World>(this);

	world->readLevel(Consts::LEVELS[this->info->levelInd]);
}

void StateInGame::onSoldierDied() {
	world->getState()->getInfo()->soldiersDied++;
}

void StateInGame::onEvent(sf::Event ev) {
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {
		getEngine()->changeState(new StateMainMenu(getEngine()));
		return;
	}

	world.get()->onEvent(ev);
	ui.get()->onEvent(ev);
}

void StateInGame::update(sf::Time delta) {
	world.get()->update(delta);
	ui.get()->update(delta);

	if (world->getSoldiers()->getLiveSoldierCnt() == 0) {
		info->prevLvlLost = true;
		getEngine()->changeState(new StateMidLevel(getEngine(), info));
	} else if (world->getTileMap()->getGoalCnt() == 0) {
		getEngine()->changeState(new StateMidLevel(getEngine(), info));
	}
}

void StateInGame::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	world.get()->draw(target, states);
	ui.get()->draw(target, states);
}