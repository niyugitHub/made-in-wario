#pragma once
#include "EnemyBase.h"
#include<list>
#include <memory>

class Enemy1;
class Enemy2;
class Player;

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

	void SetPlayer(Player* player) { m_Player = player; }

	void Init();
	void end();

	void Update();
	void Draw();

	std::shared_ptr<EnemyBase> Create(EnemyType type, const Vec2 pos);

private:

	int m_EnemyName;
	std::list<std::shared_ptr<EnemyBase>> m_Enemy;
	Player* m_Player;
};

