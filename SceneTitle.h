#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include "game.h"
#include "Player.h"

class SceneTitle : public SceneBase
{
public:
//	constexpr int kMouseSize = 134;

public:
	SceneTitle()
	{
		m_isEnd = false;
		m_IsTitleEnd = false;
		m_func = &SceneTitle::FadeinUpdate;

		for (auto& handle : m_hPlayerGraphic)
		{
			handle = -1;
		}

		m_player = new Player;

	}
	virtual ~SceneTitle() {}


	virtual void init()override;
	virtual void end() override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

	virtual bool isEnd() { return m_isEnd; }

	virtual bool isTitleEnd() { return m_IsTitleEnd; }

private:
	void FadeinUpdate();
	void TitleSceneUpdate();
	void FadeoutUpdate();

private:
	// テキストのサイズ
	int m_textSize;

	// 色の濃さ
	int m_Color;

	bool m_isEnd;

	bool m_IsTitleEnd;

	// update処理メンバ関数ポインタ
	void(SceneTitle::* m_func)();

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kCharaChipNum];

	Player* m_player;
};