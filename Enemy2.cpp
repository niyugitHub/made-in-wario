#include "Enemy2.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr int kPlayerGraphSize = 100;
	constexpr float kMoveFly = 0.1f;
}

Enemy2::Enemy2() : 
	m_Vec(3,0),
	m_Frame(0)
{
	m_func = &Enemy2::UpdatePatrol;
}

Enemy2::~Enemy2()
{
}

void Enemy2::update()
{
	m_NextPos = m_Pos;
	BasicMoveEnemy();

	m_PlayerPos = m_Player->GetPos();
	(this->*m_func)();

	m_DistancePos = m_Pos - m_PlayerPos;

	//m_NextPos = m_Pos;

	/*if (m_DistancePos.x > -500 && m_DistancePos.x < 500)
	{
		m_func = &Enemy2::UpdateDiscovery;
	}*/
}

void Enemy2::UpdatePatrol()
{
	m_Frame++;

	if (m_Frame % 180 == 0)
	{
		m_Vec.x *= -1;
	}

	m_Pos += m_Vec;

	/*m_Pos.x += m_Vec.x;

	m_NextPos += m_Vec;

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos = m_NextPos;
	}*/
}

void Enemy2::UpdateDiscovery()
{
}

void Enemy2::updateAttack()
{
}
