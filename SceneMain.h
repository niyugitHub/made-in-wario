#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"

//class Player;
//class Minigame1;
//class Vec2;
class Collision;
class Enemy1;

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

	// プレイヤーのポジション
	Vec2 m_PlayerPos;

	// エネミーのポジション
	Vec2 m_EnemyPos;

	// キャラクターとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	// エネミーとブロックの衝突判定
	bool m_CollTopEnemy;
	bool m_CollBottomEnemy;
	bool m_CollLeftEnemy;
	bool m_CollRightEnemy;

	// プレイヤーの死亡判定
	bool m_DeadPlayer;

	
	// プレイヤー
	Player*m_player;

	// マップ
	Map* m_Map;

	// 当たり判定
	Collision* m_Coll;

	// 敵
	Enemy1* m_Enemy;
};
