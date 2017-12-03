#include "GameState.hpp"
#include "Engine.hpp"
#include "GameObject.hpp"

GameState::GameState(Engine *engine) : objects(true), addPending(false) {
	this->engine = engine;
}

void GameState::destroyPendingObjects() {
	std::size_t i = 0, j = 0;
	while (j < objects.getSize()) {
		if (objects[j] != 0 && !objects[j]->isDestroyPending()) {
			objects[i] = objects[j];
			++i;
		} else {
			delete objects[j];
		}

		++j;
	}

	objects.getVector().resize(i);
}

void GameState::addPendingObjects() {
	for (std::size_t i = 0; i < addPending.getSize(); ++i)
		objects.add(addPending[i]);

	addPending.getVector().clear();
}

void GameState::addObject(GameObject *object) {
	addPending.add(object);
	object->setState(this);
}

void GameState::onEvent(sf::Event ev) {
	destroyPendingObjects();
	addPendingObjects();

	for (std::size_t i = 0; i < objects.getSize(); ++i)
		objects[i]->onEvent(ev);
}

void GameState::update(sf::Time delta) {
	destroyPendingObjects();
	addPendingObjects();

	for (std::size_t i = 0; i < objects.getSize(); ++i)
		objects[i]->update(delta);
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (std::size_t i = 0; i < objects.getSize(); ++i)
		target.draw(*objects[i], states);
}

GameState::~GameState() {
}