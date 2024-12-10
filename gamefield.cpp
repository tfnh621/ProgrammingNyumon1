#include "gamefield.h"
#include "DxLib.h"
#include "draw.h"
#include "camera.h"
#include "settings.h"
#include "scoreboard.h"
#include <cmath>
#include <algorithm>

std::vector<target> gamefield::targets(5);

void gamefield::init_targets()
{
	for (size_t i = 0; i < targets.size(); i++)
	{
		generate_target(i);
	}
}

void gamefield::on_shoot()
{
	scoreboard::add_gun_triggered();
	VECTOR from = VAdd(camera::get_pos(), VScale(camera::get_direction(), 9.5f));
	VECTOR to = VAdd(camera::get_pos(), VScale(camera::get_direction(), 14.0f));
	for (size_t i = 0; i < targets.size(); i++)
	{
		float distance_squared = Segment_Point_MinLength_Square(from, to, targets[i].center);
		if (distance_squared <= std::pow(targets[i].radius, 2))
		{
			scoreboard::add_target_hit();
			float accuracy = (targets[i].radius - std::sqrt(distance_squared)) / targets[i].radius;	// 中心からの距離の割合(中心を捉える正確性)
			scoreboard::add_score((int)(accuracy * 1000));
			generate_target(i);
		}
	}
}

void gamefield::draw_field()
{
	int range = 16;
	for (int i = -range; i <= range; i++) {
		int d = abs(i) * 1;
		unsigned int color = GetColor(224 - d, 224 - d, 224 - d);
		DrawLine3D(VGet((float)i, 0.0f, (float)-range), VGet((float)i, 0.0f, (float)range), color);
		DrawLine3D(VGet((float)-range, 0.0f, (float)i), VGet((float)range, 0.0f, (float)i), color);
	}
}

void gamefield::draw_targets()
{
	for (size_t i = 0; i < targets.size(); i++)
	{
		draw::sphere_3d(targets[i].center, targets[i].radius, 8, GetColorF(1.0f, 0.0f, 0.0f, 1.0f), TRUE);
		//DrawSphere3D(targets[i].center, targets[i].radius, 16, GetColor(234, 12, 23), GetColor(0, 0, 0), TRUE);
	}
}

// https://qiita.com/_EnumHack/items/25fc998873d1bc7d2276#%E4%B8%80%E6%A7%98%E5%88%86%E5%B8%83%E4%B9%B1%E6%95%B0
std::mt19937 gamefield::mt{ std::random_device{}() };
std::uniform_real_distribution<float> gamefield::xdist(-5.5f, 5.5f);	// 左右
std::uniform_real_distribution<float> gamefield::ydist(0.5f, 6.5f);		// 高さ
//std::uniform_real_distribution<float> gamefield::zdist(12.0f, 18.0f);	// 奥行き

void gamefield::generate_target(size_t num)
{
	targets[num].center.x = xdist(mt);
	targets[num].center.y = ydist(mt);
	//targets[num].center.z = zdist(mt);
	targets[num].center.z = 10.0f;

	targets[num].radius = difficulty::to_target_radius(settings::get_difficulty());

	for (size_t i = 0; i < targets.size(); i++)
	{
		if (num == i) continue;
		float distance_squared = std::powf(targets[i].center.x - targets[num].center.x, 2) +
			std::powf(targets[i].center.y - targets[num].center.y, 2) +
			std::powf(targets[i].center.z - targets[num].center.z, 2);
		if (targets[i].radius + targets[num].radius >= distance_squared)
		{
			generate_target(num);
			break;
		}
	}
}
