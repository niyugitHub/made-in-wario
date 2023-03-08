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
	// 何番目のシーンを選んだか
	int m_SceneNum;

	// もう一度遊ぶフラグ
	bool m_PlayAgain;
	// やめるフラグ
	bool m_Abort;

	// ゲームオーバーシーンが稼働しているとき
	bool m_ActiveGameOver;
};

