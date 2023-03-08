#pragma once
class GameOverScene
{
public:
	GameOverScene();
	~GameOverScene();

	/*void SetPlayAgain(bool GameOver) { m_PlayAgain = m_PlayAgain; }*/
	bool GetPlayAgain() { return m_PlayAgain; }

	/*void SetAbort(bool Abort) { m_Abort = Abort; }*/
	bool GetAbort() { return m_Abort; }

	// ゲームオーバーシーンがアクティブかどうか確認
	void SetActivgeGameOver(bool ActiveGameOver) { m_ActiveGameOver = ActiveGameOver; }
	bool GetActiveGameOver() { return m_ActiveGameOver; }

	void Init();
	void Update();

	void Draw();

private:
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();
private:
	// 画像取得
	int m_Handle = -1;
	// 何番目のシーンを選んだか
	int m_SceneNum;

	//// カーソルの場所
	//int m_Cursor = 0;

	// カーソル移動時になめらかにカーソルを動かす
	int m_CursorMove = 0;

	// もう一度遊ぶフラグ
	bool m_PlayAgain;
	// やめるフラグ
	bool m_Abort;

	// 透明度
	int m_Color = 0;

	// ゲームオーバーシーンが稼働しているとき
	bool m_ActiveGameOver;

	//update処理メンバ関数ポインタ
	void (GameOverScene::* m_func)();
};

