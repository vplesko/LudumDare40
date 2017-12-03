#pragma once

#include "SFML/Graphics.hpp"

class World;

class Background : public sf::Transformable, public sf::Drawable {
	World *world;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	Background(World *world);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};