#include "Enemy1.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr int PlayerGraphSize = 100;
}

Enemy1::Enemy1()
{
	m_Hp = 30;
	m_func = &Enemy1::UpdatePatrol;
}

Enemy1::~Enemy1()
{
}

void Enemy1::update()
{
	if (m_Hp <= 0)
	{
		m_Exist = false;
	}

	m_PlayerPos = m_Player->GetPos();

	m_DistancePos = m_Pos - m_PlayerPos;

	m_NextPos = m_Pos;
	(this->*m_func)();


	if (m_DistancePos.x > -500 && m_DistancePos.x < 500)
	{
		m_func = &Enemy1::UpdateDiscovery;
	}

	/*if (m_Pos.y > Game::kScreenHeight)
	{
		m_isDead = true;
	}*/
}

void Enemy1::UpdatePatrol()
{
	MoveEnemy();

	m_NextPos += m_Vec;

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos = m_NextPos;
	}
}

void Enemy1::UpdateDiscovery()
{
//	if(m_DistancePos.x > -50 && m_DistancePos.x )
	/*m_Vec.x = 0;
	m_MapVec = m_Map->GetVec();*/

	BasicMoveEnemy();

	if (!m_CollBottom)
	{
		m_Gravity += kGravity;
		m_Vec.y += m_Gravity;
	}

	else
	{
		m_Gravity = 0;
		m_Vec.y = 0;
	}

	if (m_DistancePos.x > -500 + PlayerGraphSize / 2 && m_DistancePos.x < PlayerGraphSize / 2)
	{
		m_Vec.x = m_MapVec.x + 3;
	}

	if (m_DistancePos.x >= PlayerGraphSize / 2 && m_DistancePos.x < 500 + PlayerGraphSize / 2)
	{
		m_Vec.x = m_MapVec.x - 3;
	}
	else
	{
		m_func = &Enemy1::UpdatePatrol;
	}

	m_NextPos += m_Vec;

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos = m_NextPos;
	}
}

void Enemy1::updateAttack()
{

}

