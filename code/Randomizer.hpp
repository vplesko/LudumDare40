#pragma once

class Randomizer {
public:
	static void init();

	// lower bound 0 inclusive, upper bound param inclusive
	static float genFloat(float X);
	
	// lower bound 0 inclusive, upper bound param inclusive
	static unsigned genUnsigned(unsigned X);

private:
	Randomizer();
	Randomizer(const Randomizer&);
};