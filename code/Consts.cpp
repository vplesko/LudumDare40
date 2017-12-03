#include "Consts.h"

const std::string Consts::MAIN_MENU_SCREEN("resources/pics/main_menu.png");

const std::vector<std::string> Consts::LEVELS({
	"resources/lvls/level1.txt",
	"resources/lvls/level2.txt",
	"resources/lvls/level3.txt"
});

const std::string Consts::MID_LEVEL_FONT("resources/fonts/sansation.ttf");

const sf::Vector2f Consts::TILE_SIZE(32, 32);
const sf::Vector2f Consts::BULLET_SIZE(4, 4);

const std::string Consts::BACK_TEXTURE("resources/pics/grass.png");
const std::string Consts::CURSOR_TEXTURE("resources/pics/cursor.png");
const std::string Consts::CROSSHAIR_TEXTURE("resources/pics/crosshair.png");

const float Consts::SCROLL_SPEED = 360;

const std::string Consts::SHOOT_SOUND("resources/sounds/shoot.wav");
const std::string Consts::KILL_SOUND("resources/sounds/kill.wav");
const std::string Consts::BREAK_SOUND("resources/sounds/break.wav");
const std::string Consts::DESTROY_SOUND("resources/sounds/destroy.wav");

const std::string Consts::WALL_TEXTURE("resources/pics/wall.png");
const std::string Consts::DOOR_TEXTURE("resources/pics/door.png");
const std::string Consts::DOOR_DMG_TEXTURE("resources/pics/door_damaged.png");
const std::string Consts::CAGE_TEXTURE("resources/pics/cage.png");
const std::string Consts::GOAL_TEXTURE("resources/pics/goal.png");
const std::string Consts::GOAL_DMG_TEXTURE("resources/pics/goal_damaged.png");

const int Consts::DOOR_HP(5);
const int Consts::CAGE_HP(7);
const int Consts::GOAL_HP(12);

const std::string Consts::SOLDIER_TEXTURE("resources/pics/soldier.png");
const std::string Consts::ENEMY_TEXTURE("resources/pics/enemy.png");

const int Consts::SOLDIER_HP(5);
const int Consts::SOLDIER_DMG(1);
const float Consts::SOLDIER_BULLET_SPEED(120);
const float Consts::SOLDIER_BULLET_RANGE(1.45f);

sf::Color Consts::SOLDIER_BULLET_COL(255, 255, 255);

const int Consts::ENEMY_HP(5);
const float Consts::ENEMY_SPEED(60);
const int Consts::ENEMY_DMG(1);
const float Consts::ENEMY_ATTACK_CD(.75f);
const float Consts::ENEMY_BULLET_SPEED(120);
const float Consts::ENEMY_BULLET_RANGE(1.5f);

sf::Color Consts::ENEMY_BULLET_COL(255, 255, 0);

float Consts::calcSoldierSpeed(unsigned soldierCnt) {
	return linThenCutoffFunc(160, 80, 6, soldierCnt);
}

float Consts::calcSoldierAttackCd(unsigned soldierCnt) {
	return linThenCutoffFunc(.2f, .8f, 6, soldierCnt);
}

float Consts::linThenCutoffFunc(float top, float bot, unsigned cut, unsigned x) {
	if (x >= cut) return bot;

	float k = (bot - top) / (cut - 1);
	float n = top - k;

	return k * x + n;
}