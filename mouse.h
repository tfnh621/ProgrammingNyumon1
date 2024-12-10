#pragma once
#include <functional>
#include <Windows.h>
class mouse
{
public:
	static void init_raw_input();
	static void lock_cursor();
	static void free_cursor();
private:
	static bool cursor_locked;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
