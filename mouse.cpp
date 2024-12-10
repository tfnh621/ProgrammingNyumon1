#include "mouse.h"
#include "camera.h"
#include "graphic.h"
#include "gun.h"
#include "DxLib.h"
#include "settings.h"
#include <algorithm>

bool mouse::cursor_locked = false;

void mouse::init_raw_input()
{
	// https://docs.microsoft.com/ja-jp/windows/win32/inputdev/using-raw-input#example-2
	RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = 0x01;	//HID_USAGE_PAGE_GENERIC
	Rid[0].usUsage = 0x02;		//HID_USAGE_GENERIC_MOUSE
	Rid[0].dwFlags = RIDEV_NOLEGACY;
	Rid[0].hwndTarget = 0;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	SetHookWinProc(WndProc);
}

void mouse::lock_cursor()
{
	cursor_locked = true;

	SetMouseDispFlag(FALSE);

	RECT r;
	GetClipCursor(&r);
	r.left = 0;
	r.top = 0;
	r.right = graphic::get_width();
	r.bottom = graphic::get_height();
	ClipCursor(&r);
}

void mouse::free_cursor()
{
	cursor_locked = false;

	SetMouseDispFlag(TRUE);

	ClipCursor(NULL);
}

LRESULT CALLBACK mouse::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// https://docs.microsoft.com/ja-jp/windows/win32/dxtecharts/taking-advantage-of-high-dpi-mouse-movement#wm_input
	switch (msg)
	{
	case WM_INPUT:
	{
		UINT dwSize = sizeof(RAWINPUT);
		static BYTE lpb[sizeof(RAWINPUT)];

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT* raw = (RAWINPUT*)lpb;

		if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			int xPosRelative = raw->data.mouse.lLastX;
			int yPosRelative = raw->data.mouse.lLastY;

			camera::add_vrot(yPosRelative * 0.001953125f * settings::get_sensitive());
			camera::add_hrot(xPosRelative * 0.001953125f * settings::get_sensitive());
			camera::update();

			int buttons = raw->data.mouse.usButtonFlags;
			if ((buttons & RI_MOUSE_LEFT_BUTTON_DOWN) != 0) gun::handle_left();
			else if ((buttons & RI_MOUSE_LEFT_BUTTON_UP) != 0) gun::release_left();
			if ((buttons & RI_MOUSE_RIGHT_BUTTON_DOWN) != 0) gun::handle_right();
			else if ((buttons & RI_MOUSE_RIGHT_BUTTON_UP) != 0) gun::release_right();
		}
		break;
	}
	case WM_ACTIVATE:
	{
		if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
		{
			if (cursor_locked)
			{
				lock_cursor();
			}
		}
	}
	}
	return 0;
}
