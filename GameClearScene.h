#pragma once
#include<memory>

class Particle;

class GameClearScene
{
public:
	GameClearScene(int handle);
	~GameClearScene();

	bool GetPlayAgain() { return m_PlayAgain; }

	bool GetAbort() { return m_Abort; }

	void Init();
	void Update();
	void Draw();

private:
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();
private:
	int m_handle = -1;
	// カーソルの場所
	int m_Cursor;
	// カーソル移動時になめらかにカーソルを動かす
	int m_CursorMove = 0;

	// もう一度遊ぶフラグ
	bool m_PlayAgain;
	// やめるフラグ
	bool m_Abort;

	// 透明度
	int m_Color = 0;

	//update処理メンバ関数ポインタ
	void (GameClearScene::* m_func)();

	// パーティクル
	std::shared_ptr<Particle> m_Particle;
};

