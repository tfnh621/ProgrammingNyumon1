#include "settings.h"
#include "difficulty.h"
#include <algorithm>

setting_struct settings::setting{ 1.0f, difficulty::VERY_EASY, true, true, false };

void settings::load_file()
{
	FILE* fp;
	if (fopen_s(&fp, "settings.dat", "rb") != 0) return;
	fread(&setting, sizeof(setting_struct), 1, fp);
	fclose(fp);
}

void settings::write_file()
{
	FILE* fp;
	if (fopen_s(&fp, "settings.dat", "wb") != 0) return;
	fwrite(&setting, sizeof(setting_struct), 1, fp);
	fclose(fp);
}

float settings::get_sensitive()
{
	return setting.sensitive;
}

void settings::set_sensitive(float value)
{
	setting.sensitive = std::clamp(value, 0.01f, 10.0f);
}

int settings::get_difficulty()
{
	return setting.difficulty;
}

bool settings::set_difficulty(int value)
{
	int old = setting.difficulty;
	setting.difficulty = difficulty::clamp(value);
	return old != setting.difficulty;
}

bool settings::get_vsync()
{
	return setting.vsync;
}

void settings::set_vsync(bool value)
{
	setting.vsync = value;
}

bool settings::get_anti_aliasing()
{
	return setting.anti_aliasing;
}

void settings::set_anti_aliasing(bool value)
{
	setting.anti_aliasing = value;
}

bool settings::get_print_debug()
{
	return setting.print_debug;
}

void settings::set_print_debug(bool value)
{
	setting.print_debug = value;
}
