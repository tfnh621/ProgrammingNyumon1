#pragma once
#include "DxLib.h"
class draw
{
public:
	static void graph(int x, int y, int graphic_handle, int transparent_flag);
	static void sphere_3d(VECTOR center, float r, int polygon, COLOR_F color, int fill);
	static void chara(int x, int y, const char* str, unsigned int color, int font, int size, unsigned int edge_color = 0U);
};
