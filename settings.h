#pragma once
struct setting_struct
{
	float sensitive;
	int difficulty;
	bool vsync;
	bool anti_aliasing;
	bool print_debug;
};

class settings
{
public:
	static void load_file();
	static void write_file();

	static float get_sensitive();
	static void set_sensitive(float value);
	static int get_difficulty();
	static bool set_difficulty(int value);
	static bool get_vsync();
	static void set_vsync(bool value);
	static bool get_anti_aliasing();
	static void set_anti_aliasing(bool value);
	static bool get_print_debug();
	static void set_print_debug(bool value);
private:
	static setting_struct setting;
};
