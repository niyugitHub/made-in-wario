#pragma once
#include "EnemyBase.h"
#include<list>
#include <memory>
#include "Vec2.h"

class Enemy1;
class Enemy2;
class Enemy3;
class Player;
class Particle;
class Map;
class Collision;

class EnemyFactory
{
public:
	enum EnemyType
	{
		kNormal,
		kJump,
		kThrow,
	};
public:
	EnemyFactory();
	~EnemyFactory();

	void setCategory(char EnemyName) { m_EnemyName = EnemyName; }

	Vec2 GetPos() { return m_Pos; }
	void SetPos(Vec2 Pos) { m_Pos = Pos; }

	Vec2 GetThrowPos() { return m_ThrowPos; }

	void SetPlayer(std::shared_ptr<Player> player) { m_Player = player; }
	void SetMap(std::shared_ptr<Map> map) { m_Map = map; }
	void SetColl(std::shared_ptr<Collision> Coll) { m_Coll = Coll; }

	void Init();
	void end();

	void Update();
	void Draw(Vec2 offset);

	std::shared_ptr<EnemyBase> Create(EnemyType type, const Vec2 pos);

	void AttackDamage();

	// ステージごとに度のエネミーを出現させるか
	void StageEnemy(int StageNum);

	// エネミーが死んだときの処理(ステージが変わったとき)
	void EnemyDead();

private:
	int m_EnemyName;
	int m_Frame;

	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollRight;
	bool m_CollLeft;

	//// 存在確認
	//bool m_Exist;

	Vec2 m_Pos;

	Vec2 m_ThrowPos;

	std::list<std::shared_ptr<EnemyBase>> m_Enemy;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Collision> m_Coll;
	std::shared_ptr<Particle> m_Particle;
};

