#include "camera.h"
#include "math.h"
#include <algorithm>

const float camera::eye_height = 2.0f;

VECTOR camera::position;
float camera::v_rotate = 0.0f;
float camera::h_rotate = 0.0f;
float camera::t_rotate = 0.0f;
float camera::fov = 60.0f;
bool camera::locked = false;

void camera::init()
{
	locked = false;
	SetCameraNearFar(0.9f, 29.0f);
	position = VGet(0.0f, eye_height, 0.0f);
	v_rotate = 0.0f;
	h_rotate = 0.0f;
	t_rotate = 0.0f;
	set_fov(68.0f);
	update();
}

void camera::reset_pos()
{
	v_rotate = 0.0f;
	h_rotate = 0.0f;
	t_rotate = 0.0f;
	update();
}

VECTOR camera::get_pos()
{
	return position;
}

VECTOR camera::get_direction()
{
	return VSub(GetCameraTarget(), position);
}

float camera::get_vrot()
{
	return v_rotate;
}

float camera::get_hrot()
{
	return h_rotate;
}

float camera::get_trot()
{
	return t_rotate;
}

void camera::add_vrot(float delta)
{
	if (!locked)
	{
		v_rotate = std::clamp(v_rotate + delta, -math::pi * 0.4375f, math::pi * 0.5f);
	}
}

void camera::add_hrot(float delta)
{
	if (!locked)
	{
		h_rotate += delta;
		if (h_rotate < 0.0f) h_rotate += 2.0f * math::pi;
		else if (h_rotate >= 2.0f * math::pi) h_rotate -= 2.0f * math::pi;
	}
}

void camera::add_trot(float delta)
{
	if (!locked)
	{
		t_rotate += delta;
	}
}

void camera::update()
{
	SetCameraPositionAndAngle(position, v_rotate, h_rotate, t_rotate);
}

float camera::get_fov()
{
	return fov;
}

void camera::set_fov(float fov)
{
	camera::fov = std::clamp(fov, 8.0f, 170.0f);
	SetupCamera_Perspective(math::deg2rad(fov));
}

bool camera::is_locked()
{
	return locked;
}

void camera::lock()
{
	locked = true;
}

void camera::unlock()
{
	locked = false;
}
