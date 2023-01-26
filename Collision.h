#pragma once
#include"Vec2.h"

class Player;
class Map;

class Collision
{
public:
	Collision();

	~Collision();

	void setPlayer(Player* pPlayer) { m_player = pPlayer; }
	void setMap(Map* pMap) { m_Map = pMap; }

	bool IsCollTop() { return m_CollTop; }
	bool IsCollBottom() { return m_CollBottom; }
	bool IsCollRight() { return m_CollRight; }
	bool IsCollLeft() { return m_CollLeft; }

	void Update();

	void IsCollision();

	void InitColl();

private:
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollRight;
	bool m_CollLeft;

	Vec2 m_PlayerPos;

	Player* m_player;
	Map* m_Map;
};

