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

	// エネミーとマップの当たり判定
	bool IsCollTopEnemy() { return m_CollTopEnemy; }
	bool IsCollBottomEnemy() { return m_CollBottomEnemy; }
	bool IsCollRightEnemy() { return m_CollRightEnemy; }
	bool IsCollLeftEnemy() { return m_CollLeftEnemy; }

	void Update();

	// プレイヤーとエネミーの当たり判定
	bool IsCollEnemy();

	// プレイヤーとマップの当たり判定
	void IsCollMap();

	// プレイヤーとマップの当たり判定
	void IsCollMapEnemy();

	void InitColl();

	bool FallPlayer();

	// プレイヤーの上下左右の座標
	void PlayerDirectPos();

	// エネミーの上下左右の座標
	void EnemyDirectPos();

	void MapInfo(int i,int j);

private:
	// プレイヤーとマップの当たり判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollRight;
	bool m_CollLeft;

	// エネミーとマップの当たり判定
	bool m_CollTopEnemy;
	bool m_CollBottomEnemy;
	bool m_CollRightEnemy;
	bool m_CollLeftEnemy;

	// プレイヤーとエネミーの当たり判定
	bool m_CollEnemy;

	// マップチップの当たり判定が下だけにあるとき
	bool m_CollSingle;

	// マップチップに当たり判定がないとき
	bool m_MapColl;

	Vec2 m_PlayerPos;

	Vec2 m_EnemyPos;

	Vec2 m_MapPos;

	Player* m_player;
	EnemyBase* m_enemy;
	Map* m_Map;
};

