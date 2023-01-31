#pragma once
#include"Vec2.h"

class Player;
class EnemyBase;
class Map;

class Collision
{
public:
	Collision();

	~Collision();

	void setPlayer(Player* pPlayer) { m_player = pPlayer; }
	void setMap(Map* pMap) { m_Map = pMap; }
	void setEnemy(EnemyBase* pEnemy) { m_enemy = pEnemy; }

	// プレイヤーとマップの当たり判定
	bool IsCollTop() { return m_CollTop; }
	bool IsCollBottom() { return m_CollBottom; }
	bool IsCollRight() { return m_CollRight; }
	bool IsCollLeft() { return m_CollLeft; }

	void Update();

	// プレイヤーとエネミーの当たり判定
	bool IsCollEnemy();

	void IsCollMap();

	void InitColl();

	bool FallPlayer();

private:
	// プレイヤーとマップの当たり判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollRight;
	bool m_CollLeft;

	// プレイヤーとエネミーの当たり判定
	bool m_CollEnemy;

	Vec2 m_PlayerPos;

	Vec2 m_EnemyPos;

	Vec2 m_MapPos;

	Player* m_player;
	EnemyBase* m_enemy;
	Map* m_Map;
};

