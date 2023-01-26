#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"

//class Player;
//class Minigame1;
//class Vec2;

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

	// 当たり判定
	void IsCollision();

	// 当たり判定初期化
	void isInitColl();

private:
	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kCharaChipNum];

	Vec2 m_PlayerPos;

	// キャラクターとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;
	
	// プレイヤー
	Player*m_player;

	// マップ
	Map* m_Map;
};
