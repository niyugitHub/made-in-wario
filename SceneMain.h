#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"

//class Player;
//class Minigame1;
//class Vec2;
class Collision;
class EnemyBase;

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

	// プレイヤーのポジション
	Vec2 m_PlayerPos;

	// エネミーのポジション
	Vec2 m_EnemyPos;

	// キャラクターとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	// プレイヤーの死亡判定
	bool m_DeadPlayer;

	
	// プレイヤー
	Player*m_player;

	// マップ
	Map* m_Map;

	// 当たり判定
	Collision* m_Coll;

	// 敵
	EnemyBase* m_Enemy;
};
