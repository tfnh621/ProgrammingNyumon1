#include "DxLib.h"
#include "graphic.h"
#include "math.h"
#include "draw.h"
#include "camera.h"
#include "mouse.h"
#include "gun.h"
#include "gamefield.h"
#include "settings.h"
#include "keyboard.h"
#include "scoreboard.h"
#include "font.h"
#include <stdio.h>
#include <string>

void print_debug_information();
void menu_screen();
bool in_game_screen();
void score_result_screen();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
#else
	SetOutApplicationLogValidFlag(FALSE);	// ログ出力無効
#endif
	SetMainWindowText("Game");
	SetAlwaysRunFlag(TRUE);					// DxLibを常に実行
	SetDoubleStartValidFlag(FALSE);			// 多重起動禁止
	SetMainWindowClassName("3ab611f0-9f94-4a7c-92a8-fba907f3065f");

	settings::load_file();
#ifdef _DEBUG
	settings::set_print_debug(true);
#endif

	graphic::init_before_dxlib();
	graphic::fullscreen();

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	graphic::init();
	mouse::init_raw_input();
	mouse::lock_cursor();
	camera::init();

	while (ProcessMessage() == 0)
	{
		menu_screen();
		if (ProcessMessage() != 0) break;
		bool finished = in_game_screen();
		if (ProcessMessage() != 0) break;
		if (finished) score_result_screen();
	}

	settings::write_file();

	DxLib_End();
	return 0;
}

void print_debug_information()
{
	if (settings::get_print_debug())
	{
		DrawFormatString(0, 0, 0xffffff, "FPS:%.0f", GetFPS());
		DrawFormatString(0, 16, 0xffffff, "V:%.2f, H:%.2f", math::rad2deg(camera::get_vrot()), math::rad2deg(camera::get_hrot()));
		DrawFormatString(0, 32, 0xffffff, "FOV:%.1f", camera::get_fov());
		DrawFormatString(0, 48, 0xffffff, "Sens:%.3f", settings::get_sensitive());
	}
}

void menu_screen()
{
	int selected_option = 0;
	const int available_settings = 4;

	gamefield::init_targets();

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0)
	{
		keyboard::poll_key_input();

		gamefield::draw_field();
		gamefield::draw_targets();
		gun::draw_reticle();

		if (keyboard::is_press(KEY_INPUT_DOWN) || keyboard::is_press(KEY_INPUT_S)) selected_option = std::clamp(selected_option + 1, 0, available_settings - 1);
		if (keyboard::is_press(KEY_INPUT_UP) || keyboard::is_press(KEY_INPUT_W)) selected_option = std::clamp(selected_option - 1, 0, available_settings - 1);
		switch (selected_option)
		{
		case 0:		// 難易度
			if (keyboard::is_press(KEY_INPUT_RIGHT) || keyboard::is_press(KEY_INPUT_D))
				if (settings::set_difficulty(settings::get_difficulty() + 1)) gamefield::init_targets();
			if (keyboard::is_press(KEY_INPUT_LEFT) || keyboard::is_press(KEY_INPUT_A))
				if (settings::set_difficulty(settings::get_difficulty() - 1)) gamefield::init_targets();
			break;
		case 1:		// マウス感度
			if (keyboard::is_pressing(KEY_INPUT_RIGHT) || keyboard::is_pressing(KEY_INPUT_D)) settings::set_sensitive(settings::get_sensitive() + 0.001f);
			if (keyboard::is_pressing(KEY_INPUT_LEFT) || keyboard::is_pressing(KEY_INPUT_A)) settings::set_sensitive(settings::get_sensitive() - 0.001f);
			break;
		case 2:		// VSync
			if (keyboard::is_press(KEY_INPUT_RIGHT) || keyboard::is_press(KEY_INPUT_D)) settings::set_vsync(true);
			if (keyboard::is_press(KEY_INPUT_LEFT) || keyboard::is_press(KEY_INPUT_A)) settings::set_vsync(false);
			break;
		case 3:		// アンチエイリアス
			if (keyboard::is_press(KEY_INPUT_RIGHT) || keyboard::is_press(KEY_INPUT_D)) settings::set_anti_aliasing(true);
			if (keyboard::is_press(KEY_INPUT_LEFT) || keyboard::is_press(KEY_INPUT_A)) settings::set_anti_aliasing(false);
			break;
		}
		if (keyboard::is_press(KEY_INPUT_F3)) settings::set_print_debug(!settings::get_print_debug());

		DrawStringToHandle(380, 930, "スペースキーで開始", 0xffffff, font::title, 0x000000);

		int selector = 23; int margin = 12; int vpadding = 29; int base_x = 600; int base_y = 0 + margin; int eldiff = 580;
		DrawBox(base_x - selector - margin, base_y - margin, graphic::get_width() - (base_x - selector) + margin, base_y + vpadding * available_settings + margin, 0xbbbbbb, FALSE);
		DrawStringToHandle(base_x - selector, base_y + vpadding * selected_option, ">", 0xeffafa60, font::settings);
		DrawStringToHandle(base_x, base_y + vpadding * 0, "難易度", 0xf0f0f0, font::settings);
		DrawStringToHandle(base_x, base_y + vpadding * 1, "マウス感度", 0xf0f0f0, font::settings);
		DrawStringToHandle(base_x, base_y + vpadding * 2, "垂直同期(VSync)", 0xf0f0f0, font::settings);
		DrawStringToHandle(base_x, base_y + vpadding * 3, "アンチエイリアス", 0xf0f0f0, font::settings);
		DrawFormatStringToHandle(base_x + eldiff, base_y + vpadding * 0, 0xf0f0f0, font::settings, "%s", difficulty::to_string(settings::get_difficulty()));
		DrawFormatStringToHandle(base_x + eldiff, base_y + vpadding * 1, 0xf0f0f0, font::settings, "%.3f", settings::get_sensitive());
		DrawFormatStringToHandle(base_x + eldiff, base_y + vpadding * 2, 0xf0f0f0, font::settings, "%s", settings::get_vsync() ? "ON" : "OFF");
		DrawFormatStringToHandle(base_x + eldiff, base_y + vpadding * 3, 0xf0f0f0, font::settings, "%s", settings::get_anti_aliasing() ? "ON" : "OFF");

		print_debug_information();

		if (keyboard::is_press(KEY_INPUT_ESCAPE)) DxLib_End();
		if (keyboard::is_press(KEY_INPUT_SPACE)) break;
	}
}

bool in_game_screen()
{
	scoreboard::reset();

	const int game_time_limit = 50 * 1000;
	int start_time = GetNowCount();
	bool is_started = false;

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0)
	{
		keyboard::poll_key_input();

		gamefield::draw_field();
		gamefield::draw_targets();
		gun::draw_reticle();

		int elapsed_time = 0;
		if (is_started)
		{
			elapsed_time = GetNowCount() - start_time;
			if (elapsed_time > game_time_limit) break;
		}
		else if (scoreboard::get_target_hit() > 0)
		{
			scoreboard::reset_fails();
			is_started = true;
			start_time = GetNowCount();
		}

		DrawFormatStringToHandle(graphic::get_width() / 2 - fontsize::timer / 4 * 5, 6, 0xededed, font::timer, "%5.2f", (float)(game_time_limit - elapsed_time) / 1000);
		DrawFormatStringToHandle(300, 6, 0xeaeaea, font::timer, "%d", scoreboard::get_score());
		DrawFormatStringToHandle(1500, 6, 0xeaeaea, font::timer, "%5.1f%%", (scoreboard::get_accuracy() * 100));

		print_debug_information();

		if (keyboard::is_press(KEY_INPUT_ESCAPE)) return false;
	}

	return true;
}

void score_result_screen()
{
	std::string t1 = std::to_string(scoreboard::get_score());
	char const* score_char = t1.c_str();
	std::string t2 = std::to_string(scoreboard::get_target_hit());
	char const* hit_char = t2.c_str();
	std::string t3 = std::to_string(scoreboard::get_accuracy() * 100);
	t3.append("%");
	char const* accuracy_char = t3.c_str();

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0)
	{
		keyboard::poll_key_input();

		gamefield::draw_field();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawBox(0, 0, graphic::get_width(), graphic::get_height(), 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		draw::chara(graphic::get_width() / 2, 250, "スコア", 0xeeeeee, font::timer, fontsize::timer);
		draw::chara(graphic::get_width() / 2, 450, score_char, 0xeeeeee, font::result, fontsize::result);
		
		draw::chara(350, 800, "難易度", 0xeeeeee, font::settings, fontsize::settings);
		draw::chara(350, 850, difficulty::to_string(settings::get_difficulty()), 0xeeeeee, font::timer, fontsize::timer);
		draw::chara(960, 800, "破壊した的の数", 0xeeeeee, font::settings, fontsize::settings);
		draw::chara(960, 850, hit_char, 0xeeeeee, font::timer, fontsize::timer);
		draw::chara(1570, 800, "命中率", 0xeeeeee, font::settings, fontsize::settings);
		draw::chara(1570, 850, accuracy_char, 0xeeeeee, font::timer, fontsize::timer);

		print_debug_information();

		if (keyboard::is_press(KEY_INPUT_ESCAPE) || keyboard::is_press(KEY_INPUT_SPACE)) break;
	}
}
