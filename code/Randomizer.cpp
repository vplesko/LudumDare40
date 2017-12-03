#include "Randomizer.hpp"
#include <cstdlib>
#include <ctime>

void Randomizer::init() {
	srand((unsigned)(time(0)));
	rand(); // spin it a bit
}

float Randomizer::genFloat(float X) {
	return (rand() / ((float)RAND_MAX)) * X;
}

unsigned Randomizer::genUnsigned(unsigned X) {
	unsigned r = (unsigned)(genFloat((float)(X + 1)));
	if (r > X) r = X;
	return r;
}