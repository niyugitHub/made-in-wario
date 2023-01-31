#include"Vec2.h"
#pragma once

class Map;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void SetMap(Map* pMap) { m_Map = pMap; }

	virtual void Init();
	virtual void end();

	virtual Vec2 GetPos() { return m_Pos; }

	virtual void update();
	virtual void draw();

	virtual void MoveEnemy();

	// 存在確認
	bool isExist() const { return m_isDead; }
	void setExist(bool isDead) { m_isDead = isDead; }

private:
	Vec2 m_Pos;
	Vec2 m_Vec;

	// スクロールのスピード
	Vec2 m_MapVec;

	bool m_isDead;

	Map* m_Map;
};

