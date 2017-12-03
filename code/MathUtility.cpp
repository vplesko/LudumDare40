#include "MathUtility.hpp"

const float MathUtility::Pi = 3.1415f;
const float MathUtility::twoPi = 2 * MathUtility::Pi;
const float MathUtility::sqrt2 = sqrtf(2.f);

float MathUtility::magnitudeSqr(const sf::Vector2f &v) {
	return v.x * v.x + v.y * v.y;
}

float MathUtility::magnitude(const sf::Vector2f &v) {
	return sqrtf(magnitudeSqr(v));
}

sf::Vector2f MathUtility::normalize(const sf::Vector2f &v) {
	float magn = magnitude(v);
	if (magn == 0) return sf::Vector2f();
	else return v / magn;
}

float MathUtility::magnitudeSqr(const sf::Vector3f &v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float MathUtility::magnitude(const sf::Vector3f &v) {
	return sqrtf(magnitudeSqr(v));
}

sf::Vector3f MathUtility::normalize(const sf::Vector3f &v) {
	return v / magnitude(v);
}

sf::Vector2f MathUtility::relativeLoc(const sf::Event::MouseButtonEvent &ev, const sf::Transformable *tr) {
	sf::Vector2f loc((float)ev.x, (float)ev.y);
	tr->getInverseTransform().transformPoint(loc);
	return loc;
}
