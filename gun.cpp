#include "gun.h"
#include "DxLib.h"
#include "draw.h"
#include "graphic.h"
#include "gamefield.h"
#include "camera.h"

int gun::reticle_handle = 0;
bool gun::locked = false;

void gun::handle_left()
{
	if (!locked) gamefield::on_shoot();
}

void gun::release_left()
{
}

void gun::handle_right()
{
	camera::set_fov(camera::get_fov() - 13.0f);
}

void gun::release_right()
{
	camera::set_fov(camera::get_fov() + 13.0f);
}

void gun::draw_reticle()
{
	draw::graph(graphic::get_width() / 2, graphic::get_height() / 2, reticle_handle, TRUE);
}

bool gun::is_locked()
{
	return locked;
}

void gun::lock()
{
	locked = true;
}

void gun::unlock()
{
	locked = false;
}
