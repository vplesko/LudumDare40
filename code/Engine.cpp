#include "Engine.hpp"
#include "GameState.hpp"

Engine::Engine(sf::RenderWindow &renderWindow) {
	window = &renderWindow;

	currState = 0;

	over = false;
	paused = false;

	delta = sf::seconds(1.f / 60);
}

void Engine::togglePaused() {
	if (!paused) {
		b4Pause = clock.getElapsedTime();
		paused = true;
	} else {
		clock.restart();
		paused = false;
	}
}

void Engine::setPaused(bool p) {
	if (paused == p) return;
	else togglePaused();
}

void Engine::changeState(GameState *next) {
	if (currState) {
		currState->onLeave();
		delete currState;
	}

	currState = next;
	next->onEnter();

	accum = b4Pause = sf::Time();
	clock.restart();
}

void Engine::onEvent(const sf::Event &ev) {
	switch (ev.type) {
	case sf::Event::LostFocus:
		//setPaused(true);
		break;
	case sf::Event::GainedFocus:
		//setPaused(false);
		break;
	default:
		if (currState) currState->onEvent(ev);
		break;
	}
}

void Engine::onTime() {
	if (paused) return;

	// Approach 1:

	/*if (currState) currState->update(clock.restart() + b4Pause);*/
	
	// Approach 2:

	/*for (accum += clock.restart() + b4Pause; accum >= delta; accum -= delta) {
		if (currState) currState->update(delta);
	}*/
	
	// Approach 3:

	for (accum = clock.restart() + b4Pause; accum >= delta; accum -= delta) {
		if (currState) currState->update(delta);
	}

	if (accum > sf::Time() && currState) currState->update(accum);
	
	// Approach 4:
	
	/*accum += clock.restart() + b4Pause;
	if (accum >= delta) {
		accum -= delta;
		if (currState) currState->update(delta);
	}*/
	
	// After each:
	
	b4Pause = sf::Time();
}

void Engine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (currState) target.draw(*currState, states);
}

Engine::~Engine() {
	delete currState;
}
