#pragma once
enum class keystate { none, press, pressing, release };
class keyboard
{
public:
	static void poll_key_input();
	static keystate get_state(int key);
	static bool is_press(int key);
	static bool is_pressing(int key);
	static bool is_release(int key);
private:
	static int keys[256];
	static keystate keystates[256];
};
