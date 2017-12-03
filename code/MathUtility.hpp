#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class MathUtility {
public:
	static const float Pi, twoPi, sqrt2;
	
	static float magnitudeSqr(const sf::Vector2f &v);
	static float magnitude(const sf::Vector2f &v);
	static sf::Vector2f normalize(const sf::Vector2f &v);

	static float magnitudeSqr(const sf::Vector3f &v);
	static float magnitude(const sf::Vector3f &v);
	static sf::Vector3f normalize(const sf::Vector3f &v);

	static sf::Vector2f relativeLoc(const sf::Event::MouseButtonEvent &ev, const sf::Transformable *tr);

private:
	MathUtility();
	MathUtility(const MathUtility&);
};
