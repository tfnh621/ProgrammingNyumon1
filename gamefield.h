#pragma once
#include <vector>
#include <random>
#include "target.h"
#include "difficulty.h"
class gamefield
{
public:
	static void init_targets();
	static void on_shoot();
	static void draw_field();
	static void draw_targets();
private:
	static std::vector<target> targets;
	static void generate_target(size_t i);
	// —”¶¬
	static std::mt19937 mt;
	static std::uniform_real_distribution<float> xdist;
	static std::uniform_real_distribution<float> ydist;
	//static std::uniform_real_distribution<float> zdist;
};
