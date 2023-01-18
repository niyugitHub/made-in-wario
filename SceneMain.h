#pragma once
#include"SceneBase.h"
#include"Player.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	virtual void init();
	// 終了処理
	virtual void end();

	virtual SceneBase* update();
	virtual void draw();

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kCharaChipNum];
	// プレイヤー
	Player*m_player;
};
