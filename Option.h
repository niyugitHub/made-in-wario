#pragma once
class Option
{
public:
	Option(int GuideHandle, int GuideStringHandle);
	~Option();

	// オプションがアクティブかどうか確認
	void SetActivgeOption(bool OptionScene) { m_OptionScene = OptionScene; }
	bool GetActiveOption() { return m_OptionScene; }

	bool GetGuide() { return m_Guide; }

	// タイトル画面のオプションかどうか
	void SetTitleOption(bool TitleScene) { m_TitleScene = TitleScene; }

	// 

	// 画像をセット
	void SetHandle(int handle) { m_OptionHandle = handle; }

	bool GetGameEnd() { return m_GameEnd; }

	void Init();
	void Update();

	void Draw();

	void CursorMove();

private:
	void FirstUpdate();
	void GamePadUpdate();
	void EndUpdate();

	void OptionDraw();
	void GamepadDraw();
	void GameEndDraw();
private:
	// 画像取得
	int m_OptionHandle = -1;
	int m_StringHandle = -1;
	int m_GamepadHandle = -1;
	int m_GameEndHandle = -1;
	// ガイドのハンドル
	int m_GuideHandle = -1;
	int m_GuideStringHandle = -1;

	// 何番目のシーンを選んだか
	int m_SceneNum;

	// カーソル移動時になめらかにカーソルを動かす
	int m_CursorMove = 0;

	// 透明度
	int m_Color = 0;

	// オプションシーンが稼働しているとき
	bool m_OptionScene;

	// ガイドの表示の有無
	bool m_Guide;

	// ゲーム終了フラグ
	bool m_GameEnd = false;

	bool m_TitleScene = false;

	// いきなりゲーム終了にならないように
	int m_GameCount = 0;

	//update処理メンバ関数ポインタ
	void (Option::* m_func)();

	//draw処理メンバ関数ポインタ
	void (Option::* m_drawfunc)();
};

