#pragma once

#include "SFML/Graphics.hpp"
#include "GameState.hpp"

class GameObject : public sf::Drawable, public sf::Transformable {
	GameState *state;

	bool destroyPending;

public:
	GameObject();

	const GameState* getState() const { return state; }
	GameState* getState() { return state; }
	void setState(GameState *state) { this->state = state; }

	bool isDestroyPending() const { return destroyPending; }
	void setDestroyPending(bool pending) { destroyPending = pending; }

	virtual int getTag() const { return 0; }

	virtual void onEvent(sf::Event ev) {}

	virtual void update(sf::Time delta) {}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}

	virtual ~GameObject() {}
};
