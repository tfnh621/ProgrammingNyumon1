#pragma once
#include <vector>
class difficulty
{
public:
	static const int VERY_EASY = 0;
	static const int EASY = 1;
	static const int NORMAL = 2;
	static const int HARD = 3;
	static const int VERY_HARD = 4;

	static int clamp(int d);
	static const char* to_string(int d);
	static float to_target_radius(int d);
};
