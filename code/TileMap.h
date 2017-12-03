#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>

class World;
class Tiled;

class TileMap : public sf::Drawable, public sf::Transformable {
	World *world;

	unsigned w, h;
	Tiled ***map;

	unsigned goalCnt;

	std::vector<std::shared_ptr<Tiled>> tiledObjs;

public:
	TileMap(World *world);

	World* getWorld() { return world; }

	unsigned getGoalCnt() const { return goalCnt; }
	void onGoalDestroyed() { --goalCnt; }

	void readAddObjs(std::ifstream &in);

	Tiled* getObj(unsigned x, unsigned y);
	Tiled* getObjAtPos(sf::Vector2f v);
	void setObj(unsigned x, unsigned y, Tiled *t);
	void setObjAtPos(sf::Vector2f v, Tiled *t);

	void onEvent(sf::Event ev);
	void update(sf::Time delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};