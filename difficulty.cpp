#include "difficulty.h"
#include <algorithm>

int difficulty::clamp(int d)
{
	return std::clamp(d, VERY_EASY, VERY_HARD);
}

const char* difficulty::to_string(int d)
{
	switch (d)
	{
	case VERY_EASY: return "とても簡単";
	case EASY: return "簡単";
	case NORMAL: return "普通";
	case HARD: return "難しい";
	case VERY_HARD: return "とても難しい";
	default: return nullptr;
	}
}

float difficulty::to_target_radius(int d)
{
	switch (d)
	{
	case VERY_EASY: return 0.5f;
	case EASY: return 0.375f;
	case NORMAL: return 0.25f;
	case HARD: return 0.125f;
	case VERY_HARD: return 0.0625f;
	default: return 0.0f;
	}
}
