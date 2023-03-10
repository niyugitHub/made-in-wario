#include "DxLib.h"

#include"Vec2.h"
#include"SceneManager.h"
#include"Player.h"
#include"game.h"

namespace
{
	// ウインドウモード設定
	constexpr bool kWindouwMode = Game::kWindowMode;
	// ウインドウ名
	const char* const kTitleText = "ゲーム名";
	// ウインドウサイズ
	constexpr int kScreenWidth = Game::kScreenWidth;
	constexpr int kScreenHeight = Game::kScreenHeight;
	// カラーモード
	constexpr int kColorDepth = 32;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(kWindouwMode);
	
	// ウインドウ名設定
	SetMainWindowText("ゲーム名");
	// 画面サイズの設定
	SetGraphMode(kScreenWidth, kScreenHeight, 32);

	SetWindowText("HELLO KNIGHT");

	//ChangeWindowModeとSetWindowTextは、例外的にDxLib_Init()の前に書いてますが
	//基本的にDxLibの関数はDxLib_Init()実行後に書いてください
	if (DxLib_Init() == -1)	// DXライブラリ初期化処理
	{
		return -1;		// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager scene;
	scene.init();
	
	// フルスクリーンとウィンドウモードを切り替える
	/*bool isWindowMode = kWindouwMode;
	bool isTriggerEnter = false;*/
	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		SetMouseDispFlag(1);

		auto fps = GetFPS();// Frame Per Second

		// フルスクリーンとウィンドウモードを切り替える
		/*if (DxLib::CheckHitKey(KEY_INPUT_LALT))
		{
			if (DxLib::CheckHitKey(KEY_INPUT_RETURN))
			{
				if (!isTriggerEnter)
				{
					isWindowMode = !isWindowMode;
					ChangeWindowMode(isWindowMode);
				}
					isTriggerEnter = true;
			}
			else
			{
				isTriggerEnter = false;
			}
		}*/

		scene.update();
		scene.draw();

		DrawFormatString(10, 10, 0xffffff,"FPS=%2.2f", fps);
		// 裏画面と表画面を入れ替える
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	scene.end();
	/*player.end();*/

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}