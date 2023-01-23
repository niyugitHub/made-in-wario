#pragma once
#include"Vec2.h"

class Player;
class Minigame1;

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
	Minigame1* m_Map;
};

