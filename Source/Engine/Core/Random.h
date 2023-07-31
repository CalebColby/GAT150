#pragma once
#include <random>

namespace neu 
{
	inline void seedRandom(unsigned int seed) { srand(seed); }

	inline int random() { return rand(); }
	inline int random(unsigned int max) { return rand() % max; } // exclusive max
	inline int random(unsigned int min, unsigned int max) { return min + random(max - min + 1); } //inclusive min and max

	inline float randomf() { return random() / (float)RAND_MAX; } // returns decimal between 0 and 1;
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(float min, float max) { return min + randomf(max - min); }
}