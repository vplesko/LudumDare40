#pragma once

#include "SFML/Graphics.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include "SfmlResources.hpp"

class GameState;

class Engine : public sf::Drawable {
	bool over, paused;

	sf::Time accum, delta, b4Pause;
	sf::Clock clock;

	sf::RenderWindow *window;

	sf::Color clearColor;

	SfmlResources<sf::Font> fontResources;
	SfmlResources<sf::SoundBuffer> soundBufferResources;
	SfmlResources<sf::Texture> textureResources;

	GameState *currState;

public:
	Engine(sf::RenderWindow &renderWindow);

	bool isOver() const { return over; }
	void setOver(bool o) { over = o; }

	bool isPaused() const { return paused; }
	void setPaused(bool p);
	void togglePaused();

	const sf::RenderWindow& getWindow() const { return *window; }
	sf::RenderWindow& getWindow() { return *window; }

	const sf::Color& getClearColor() const { return clearColor; }
	void setClearColor(const sf::Color &col) { clearColor = col; }

	SfmlResources<sf::Font>& getFonts() { return fontResources; }
	SfmlResources<sf::SoundBuffer>& getSoundBuffers() { return soundBufferResources; }
	SfmlResources<sf::Texture>& getTextures() { return textureResources; }

	void changeState(GameState *next);

	void onEvent(const sf::Event &ev);

	void onTime();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~Engine();
};