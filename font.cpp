#include "font.h"
#include "settings.h"
#include "DxLib.h"

int font::title;
int font::settings;
int font::timer;
int font::result;

void font::init()
{
	int type = settings::get_anti_aliasing() ? DX_FONTTYPE_ANTIALIASING_EDGE_8X8 : DX_FONTTYPE_EDGE;
	title = CreateFontToHandle(NULL, fontsize::title, -1, type);
	settings = CreateFontToHandle(NULL, fontsize::settings, -1, type);
	timer = CreateFontToHandle(NULL, fontsize::timer, -1, type);
	result = CreateFontToHandle(NULL, fontsize::result, -1, type);
}
