#pragma once
#include"Vec2.h"

class Player;
class Map;

class Collision
{
public:
	Collision();

	~Collision();

	void Update();

	bool IsCollTop();
	bool IsCollBottom();
	bool IsCollLeft();
	bool IsCollRight();

private:
	Vec2 m_PlayerPos;

	Player* m_player;
	Map* m_Map;
};

