#include "TileMap.h"
#include "Tiled.h"
#include "Consts.h"
#include "Wall.h"
#include <fstream>
#include "Door.h"
#include "Goal.h"
#include "Cage.h"

TileMap::TileMap(World *world) {
	this->world = world;

	// lazy workaround
	this->w = 1000;
	this->h = 1000;

	goalCnt = 0;

	map = new Tiled**[w];
	for (unsigned i = 0; i < w; ++i) {
		map[i] = new Tiled*[h];
		for (unsigned j = 0; j < h; ++j) {
			map[i][j] = 0;
		}
	}
}

void TileMap::readAddObjs(std::ifstream &in) {
	std::string name;
	unsigned cnt;
	float x, y;

	while (!in.eof()) {
		std::getline(in, name);
		in >> cnt;

		if (cnt > 0) {
		if (name.compare("Wall") == 0) {
				for (unsigned i = 0; i < cnt; ++i) {
					in >> x >> y;
					Wall *obj = new Wall(this);
					setObjAtPos(sf::Vector2f(x, y), obj);
				}
			} else if (name.compare("Door") == 0) {
				for (unsigned i = 0; i < cnt; ++i) {
					in >> x >> y;
					Door *obj = new Door(this);
					setObjAtPos(sf::Vector2f(x, y), obj);
				}
			} else if (name.compare("Goal") == 0) {
				for (unsigned i = 0; i < cnt; ++i) {
					in >> x >> y;
					Goal *obj = new Goal(this);
					setObjAtPos(sf::Vector2f(x, y), obj);
					++goalCnt;
				}
			}
			else if (name.compare("Cage") == 0) {
				for (unsigned i = 0; i < cnt; ++i) {
					in >> x >> y;
					Cage *obj = new Cage(this);
					setObjAtPos(sf::Vector2f(x, y), obj);
				}
			}
		} else {
			std::getline(in, name);
		}

		std::getline(in, name);
		std::getline(in, name);
	}
}

Tiled* TileMap::getObj(unsigned x, unsigned y) {
	if (x >= w || y >= h) return 0;
	if (map[x][y] == 0 || map[x][y]->isDestroyed()) return 0;
	else return map[x][y];
}

Tiled* TileMap::getObjAtPos(sf::Vector2f v) {
	if (v.x * v.y < 0) return 0;

	unsigned x = (unsigned)(v.x / Consts::TILE_SIZE.x);
	unsigned y = (unsigned)(v.y / Consts::TILE_SIZE.y);

	return getObj(x, y);
}

void TileMap::setObj(unsigned x, unsigned y, Tiled *t) {
	for (unsigned i = 0; i < t->getW(); ++i) {
		for (unsigned j = 0; j < t->getH(); ++j) {
			map[x + i][y + j] = t;
		}
	}

	tiledObjs.push_back(std::shared_ptr<Tiled>(t));

	t->setPosition(x * Consts::TILE_SIZE.x, y * Consts::TILE_SIZE.y);
	t->setX(x);
	t->setY(y);
}

void TileMap::setObjAtPos(sf::Vector2f v, Tiled *t) {
	if (v.x * v.y < 0) return;

	unsigned x = (unsigned)(v.x / Consts::TILE_SIZE.x);
	unsigned y = (unsigned)(v.y / Consts::TILE_SIZE.y);

	setObj(x, y, t);
}

void TileMap::onEvent(sf::Event ev) {
	for (auto it : tiledObjs) {
		if (!it->isDestroyed())
			it->onEvent(ev);
	}
}

void TileMap::update(sf::Time delta) {
	for (auto it : tiledObjs) {
		if (!it->isDestroyed())
			it->update(delta);
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto it : tiledObjs) {
		if (!it->isDestroyed())
			it->draw(target, states);
	}
}