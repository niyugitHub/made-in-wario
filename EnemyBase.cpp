#include "EnemyBase.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

EnemyBase::EnemyBase() : 
	m_Pos(0,900),
	m_Vec(3,0),
	m_MapVec(0,0),
	m_isDead(false),
	m_Map(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::end()
{
}

void EnemyBase::update()
{
	MoveEnemy();
}

void EnemyBase::draw()
{
	DrawBox(m_Pos.x, m_Pos.y, m_Pos.x + 50,m_Pos.y + 50,GetColor(255, 0, 0), true);
}

void EnemyBase::MoveEnemy()
{
	m_Vec.x = 3;
	/*if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_Vec.x -= 5;
		if (CheckHitKey(KEY_INPUT_RSHIFT) || CheckHitKey(KEY_INPUT_LSHIFT))
		{
			m_Vec.x -= 5;
		}
		
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_Vec.x += 5;
		if (CheckHitKey(KEY_INPUT_RSHIFT) || CheckHitKey(KEY_INPUT_LSHIFT))
		{
			m_Vec.x += 5;
		}
	}*/

	m_MapVec = m_Map->GetVec();

//	assert(m_MapVec.x == 0);

	m_Vec += m_MapVec;


	m_Pos += m_Vec;
}
