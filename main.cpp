#include "DxLib.h"

#include"Vec2.h"
#include"SceneManager.h"

namespace
{
	// ウインドウモード設定
	constexpr bool kWindouwMode = true;
	// ウインドウ名
	const char* const kTitleText = "ゲーム名";
	// ウインドウサイズ
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	// カラーモード
	constexpr int kColorDepth = 32;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// windowモード設定
	ChangeWindowMode(kWindouwMode);
	// ウインドウ名設定
	SetMainWindowText("ゲーム名");
	// 画面サイズの設定
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1)	// DXライブラリ初期化処理
	{
		return -1;		// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager scene;
	scene.init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		SetMouseDispFlag(1);

		scene.update();
		scene.draw();

		// 裏画面と表画面を入れ替える
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	scene.end();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}