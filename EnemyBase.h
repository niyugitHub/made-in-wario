#include"Vec2.h"
#pragma once

class Map;
class Player;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void SetMap(Map* pMap) { m_Map = pMap; }
	virtual void SetPlayer(Player* pPlayer) { m_Player = pPlayer; }

	virtual void SetCollTop(bool Top) { m_CollTop = Top; }
	virtual void SetCollBottom(bool Bottom) { m_CollBottom = Bottom; }
	virtual void SetCollRight(bool Right) { m_CollRight = Right; }
	virtual void SetCollLeft(bool Left) { m_CollLeft = Left; }

	virtual void SetPos(Vec2 Pos) { m_Pos = Pos; }

	virtual void Init();
	virtual void end();

	virtual Vec2 GetPos() { return m_Pos; }

	virtual void update();
	virtual void draw();

	virtual void MoveEnemy();

	// 存在確認
	bool isExist() const { return m_isDead; }
	void setExist(bool isDead) { m_isDead = isDead; }

protected:
	Vec2 m_Pos;
	Vec2 m_Vec;

	// プレイヤーの座標
	Vec2 m_PlayerPos;

	// プレイヤーとエネミーの座標の差
	Vec2 m_DistancePos;

	float m_Gravity;

	// 壁に当たった時に逆方向に進むための変数
	int m_MoveInverseDirection;

	// スクロールのスピード
	Vec2 m_MapVec;

	// 死亡判定
	bool m_isDead;

	// エネミーとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	Player* m_Player;
	Map* m_Map;
};

