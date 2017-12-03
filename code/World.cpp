#include "World.h"
#include "StateInGame.h"
#include "MathUtility.hpp"
#include "Wall.h"
#include <fstream>
#include "Consts.h"

World::World(StateInGame *state) {
	this->state = state;

	background = std::make_shared<Background>(this);
	soldiers = std::make_shared<SoldierManager>(this);
	enemies = std::make_shared<EnemyManager>(this);
	bullets = std::make_shared<BulletManager>(this);
	tileMap = std::make_shared<TileMap>(this);
}

void World::readLevel(std::string filename) {
	std::ifstream in(filename);
	std::string dummy;
	unsigned cnt;
	
	std::getline(in, dummy);
	in >> cnt;
	if (cnt > 0) {
		float x, y;
		in >> x >> y;
		sf::Vector2f pos = (sf::Vector2f) getState()->getEngine()->getWindow().getSize() / 2.f;
		pos -= sf::Vector2f(x, y);
		setPosition(pos);
	} else {
		std::getline(in, dummy);
	}

	std::getline(in, dummy);
	std::getline(in, dummy);
	std::getline(in, dummy);
	soldiers->readAddSoldiers(in);
	
	std::getline(in, dummy);
	std::getline(in, dummy);
	std::getline(in, dummy);
	enemies->readAddEnemies(in);

	std::getline(in, dummy);
	std::getline(in, dummy);
	tileMap->readAddObjs(in);

	in.close();
}

void World::onEvent(sf::Event ev) {
	if (ev.type == sf::Event::MouseButtonPressed ||
		ev.type == sf::Event::MouseButtonReleased) {
		sf::Vector2f mod((float)ev.mouseButton.x, (float)ev.mouseButton.y);
		mod = getInverseTransform().transformPoint(mod);

		ev.mouseButton.x = (int)mod.x;
		ev.mouseButton.y = (int)mod.y;
	}

	soldiers.get()->onEvent(ev);
	enemies.get()->onEvent(ev);
	bullets->onEvent(ev);
	tileMap->onEvent(ev);
}

void World::update(sf::Time delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		move(Consts::SCROLL_SPEED * delta.asSeconds() * sf::Vector2f(0, +1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		move(Consts::SCROLL_SPEED * delta.asSeconds() * sf::Vector2f(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		move(Consts::SCROLL_SPEED * delta.asSeconds() * sf::Vector2f(+1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		move(Consts::SCROLL_SPEED * delta.asSeconds() * sf::Vector2f(-1, 0));

	soldiers.get()->update(delta);
	enemies.get()->update(delta);
	bullets->update(delta);
	tileMap->update(delta);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	background->draw(target, states);
	tileMap.get()->draw(target, states);
	soldiers.get()->draw(target, states);
	enemies.get()->draw(target, states);
	bullets.get()->draw(target, states);
}