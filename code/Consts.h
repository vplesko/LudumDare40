#pragma once

#include "SFML/Graphics.hpp"

struct Consts {
	static const std::string MAIN_MENU_SCREEN;

	static const std::vector<std::string> LEVELS;

	static const std::string MID_LEVEL_FONT;

	static const sf::Vector2f TILE_SIZE;
	static const sf::Vector2f BULLET_SIZE;

	static const std::string BACK_TEXTURE;
	static const std::string CURSOR_TEXTURE;
	static const std::string CROSSHAIR_TEXTURE;

	static const float SCROLL_SPEED;

	static const std::string SHOOT_SOUND;
	static const std::string KILL_SOUND;
	static const std::string BREAK_SOUND;
	static const std::string DESTROY_SOUND;

	static const std::string WALL_TEXTURE;
	static const std::string DOOR_TEXTURE, DOOR_DMG_TEXTURE;
	static const std::string CAGE_TEXTURE;
	static const std::string GOAL_TEXTURE, GOAL_DMG_TEXTURE;

	static const int DOOR_HP;
	static const int CAGE_HP;
	static const int GOAL_HP;

	static const std::string SOLDIER_TEXTURE;
	static const std::string ENEMY_TEXTURE;

	static const float SOLDIER_SPEED_BEST, SOLDIER_SPEED_WORST;
	static const unsigned SOLDIER_SPEED_WORST_AT;
	static const int SOLDIER_HP;
	static const int SOLDIER_DMG;
	static const float SOLDIER_ATTACK_CD_BEST, SOLDIER_ATTACK_CD_WORST;
	static const unsigned SOLDIER_ATTACK_CD_WORST_AT;
	static const float SOLDIER_BULLET_SPEED;
	static const float SOLDIER_BULLET_RANGE;

	static float calcSoldierSpeed(unsigned soldierCnt);
	static float calcSoldierAttackCd(unsigned soldierCnt);

	static sf::Color SOLDIER_BULLET_COL;

	static const int ENEMY_HP;
	static const float ENEMY_SPEED;
	static const int ENEMY_DMG;
	static const float ENEMY_ATTACK_CD;
	static const float ENEMY_BULLET_SPEED;
	static const float ENEMY_BULLET_RANGE;

	static sf::Color ENEMY_BULLET_COL;

private:
	static float linThenCutoffFunc(float top, float bot, unsigned cut, unsigned x);
};