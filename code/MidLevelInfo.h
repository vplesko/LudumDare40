#pragma once

struct MidLevelInfo {
	unsigned levelInd;
	unsigned soldiersDied;
	bool prevLvlLost;

	MidLevelInfo() {
		levelInd = 0;
		soldiersDied = 0;
		prevLvlLost = false;
	}
};