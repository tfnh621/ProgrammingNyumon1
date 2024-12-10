#include "math.h"
#include <numbers>

const float math::pi = (float)std::numbers::pi;

float math::deg2rad(float degree)
{
	return degree * pi / 180.0f;
}

double math::deg2rad(double degree)
{
	return degree * std::numbers::pi / 180.0;
}

float math::rad2deg(float radian)
{
	return radian * 180.0f / pi;
}

double math::rad2deg(double radian)
{
	return radian * 180.0 / std::numbers::pi;
}
