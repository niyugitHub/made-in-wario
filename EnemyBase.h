#include"Vec2.h"
#pragma once

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void end();

	virtual Vec2 GetPos() { return m_Pos; }

	virtual void update();
	virtual void draw();

	virtual void MoveEnemy();

	// ë∂ç›ämîF
	bool isExist() const { return m_isDead; }
	void setExist(bool isDead) { m_isDead = isDead; }

private:
	Vec2 m_Pos;
	Vec2 m_Vec;

	bool m_isDead;
};

