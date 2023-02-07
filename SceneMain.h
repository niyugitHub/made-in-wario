#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"
#include <memory>

//class Player;
//class Minigame1;
//class Vec2;
class Collision;
class EnemyFactory;
class Item;

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

	// マップのポジション初期化
	Vec2 m_MapPos;

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

	// プレイヤーの存在確認
	bool m_Exist;

	
	// プレイヤー
	std::shared_ptr<Player> m_player;

	// マップ
	std::shared_ptr<Map> m_Map;

	// 当たり判定
	std::shared_ptr<Collision> m_Coll;

	// アイテム
	std::shared_ptr<Item> m_Item;

	// 敵全部
	std::shared_ptr<EnemyFactory> m_EnemyFactory;
};
