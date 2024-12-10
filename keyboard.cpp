#include "keyboard.h"
#include "DxLib.h"

int keyboard::keys[256];
keystate keyboard::keystates[256];

void keyboard::poll_key_input()
{
	static char buf[256];
	GetHitKeyStateAll(buf);
	for (size_t i = 0; i < 256; i++)
	{
		keystates[i] = keys[i] != buf[i] ?
			(buf[i] == 0 ? keystate::release : keystate::press) :
			(buf[i] == 0 ? keystate::none : keystate::pressing);
		keys[i] = buf[i];
	}
}

keystate keyboard::get_state(int key)
{
	return keystates[key];
}

bool keyboard::is_press(int key)
{
	return keystates[key] == keystate::press;
}

bool keyboard::is_pressing(int key)
{
	return keystates[key] == keystate::pressing;
}

bool keyboard::is_release(int key)
{
	return keystates[key] == keystate::release;
}
