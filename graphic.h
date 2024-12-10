#pragma once
class graphic
{
public:
	static void fullscreen();
	static void window_fullscreen();
	static int get_width();
	static int get_height();
	static void init();
	static void init_before_dxlib();
private:
	static int screen_width;
	static int screen_height;
	static int screen_color_bit;
	static void fetch_screen_resolution();
	static int game_width;
	static int game_height;
};
