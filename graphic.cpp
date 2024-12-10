#include "graphic.h"
#include "DxLib.h"
#include "gun.h"
#include "settings.h"
#include "font.h"

int graphic::screen_width;
int graphic::screen_height;
int graphic::screen_color_bit;
int graphic::game_width = 1920;
int graphic::game_height = 1080;

void graphic::fullscreen()
{
	fetch_screen_resolution();

	//ChangeWindowMode(FALSE);		// フルスクリーン
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	SetGraphMode(game_width, game_height, screen_color_bit, GetRefreshRate());
}

void graphic::window_fullscreen()
{
	fetch_screen_resolution();

	ChangeWindowMode(TRUE);		// ウィンドウモード
	SetWindowStyleMode(2);		// タイトルなしフチなし
	//SetWindowSizeChangeEnableFlag(FALSE);	// サイズ変更不可
	SetGraphMode(game_width, game_height, screen_color_bit, GetRefreshRate());
	SetWindowSize(screen_width, screen_height);
}

int graphic::get_width()
{
	return game_width;
}

int graphic::get_height()
{
	return game_height;
}

void graphic::init()
{
	// 画像読み込み
	gun::reticle_handle = LoadGraph("reticle.bmp");

	// 設定
	SetBackgroundColor(10, 10, 12);

	// DxLibの3D設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// DxLibのライト設定 (ライト系の関数ではaは使われない)
	SetGlobalAmbientLight(GetColorF(0.375f, 0.375f, 0.375f, 0.0f));
	SetLightDirection(VECTOR(0.75f, -1.0f, 1.0f));
	//ChangeLightTypePoint(VGet(-50.0f, 50.0f, -100.0f), 200.0f, 1.75f, 0.0f, 0.0f);

	// フォント初期化
	font::init();
}

void graphic::init_before_dxlib()
{
	SetWaitVSyncFlag(settings::get_vsync() ? TRUE : FALSE);
	if(settings::get_anti_aliasing()) SetFullSceneAntiAliasingMode(2, 1);
}

void graphic::fetch_screen_resolution()
{
	GetDefaultState(&screen_width, &screen_height, &screen_color_bit);
}
