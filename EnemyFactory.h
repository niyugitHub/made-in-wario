#pragma once
#include "EnemyBase.h"
#include<list>
#include <memory>
#include "Vec2.h"

class Enemy1;
class Enemy2;
class Player;
class Map;
class Collision;

class EnemyFactory
{
public:
	enum EnemyType
	{
		kNormal,
		kJump,
	};
public:
	EnemyFactory();
	~EnemyFactory();

	void setCategory(char EnemyName) { m_EnemyName = EnemyName; }

	void SetPlayer(std::shared_ptr<Player> player) { m_Player = player; }
	void SetMap(std::shared_ptr<Map> map) { m_Map = map; }
	void SetColl(std::shared_ptr<Collision> Coll) { m_Coll = Coll; }

	void Init();
	void end();

	void Update();
	void Draw();

	std::shared_ptr<EnemyBase> Create(EnemyType type, const Vec2 pos);

private:
	Vec2 m_EnemyPos;
	int m_EnemyName;
	int m_Frame;

	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollRight;
	bool m_CollLeft;


	std::list<std::shared_ptr<EnemyBase>> m_Enemy;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Collision> m_Coll;
};

