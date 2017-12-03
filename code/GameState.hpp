#pragma once

#include "SFML/Graphics.hpp"
#include "VectorWrapper.hpp"
#include "Engine.hpp"

class GameObject;

class GameState : public sf::Drawable {
	Engine *engine;

	VectorWrapper<GameObject*> objects, addPending;

	void destroyPendingObjects();
	void addPendingObjects();

public:
	GameState(Engine *engine);

	const Engine* getEngine() const { return engine; }
	Engine* getEngine() { return engine; }

	std::size_t getObjectCnt() const { return objects.getSize(); }

	const GameObject* getObject(std::size_t index) const { return objects[index]; }
	GameObject* getObject(std::size_t index) { return objects[index]; }

	void addObject(GameObject *object);

	virtual void onEnter() {}

	virtual void onLeave() {}

	virtual void onEvent(sf::Event ev);

	virtual void update(sf::Time delta);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual ~GameState();
};
