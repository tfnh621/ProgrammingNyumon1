#pragma once
#include "DxLib.h"
class camera
{
public:
	static const float eye_height;

	static void init();
	static void reset_pos();
	static VECTOR get_pos();
	static VECTOR get_direction();
	static float get_vrot();
	static float get_hrot();
	static float get_trot();
	static void add_vrot(float delta);
	static void add_hrot(float delta);
	static void add_trot(float delta);
	static void update();
	static float get_fov();
	static void set_fov(float fov);
	static bool is_locked();
	static void lock();
	static void unlock();
private:
	static VECTOR position;
	static float v_rotate;	// YŽ²
	static float h_rotate;	// XZŽ²
	static float t_rotate;	// ???
	static float fov;
	static bool locked;
};
