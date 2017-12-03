#pragma once

#include "SFML/Graphics.hpp"

class Ui;

class Cursor : public sf::Transformable, public sf::Drawable {
	Ui *ui;

	bool crosshair;
	sf::Sprite sprite;

public:
	Cursor(Ui *ui);

	sf::Vector2f getWorldPosition() const;

	void setShowCrosshair(bool b);

	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};