#include "Enemy1.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr int PlayerGraphSize = 100;

	// ‰æ‘œ‚ÌƒTƒCƒY
	constexpr float kGraphSizeX = 64.0f;
	constexpr float kGraphSizeY = 64.0f;

	// ‰æ‘œ‚Ì’ZŒa•”•ª•\Ž¦
	constexpr int kRectGraphY = 128;
	constexpr int kRectGraphX = 64;
}

Enemy1::Enemy1() : 
	m_Frame(0)
{
	m_GraphX = 0;
	m_GraphY = 64;
	m_Hp = 30;
	m_GraphSize1 = { 10,10 };
	m_GraphSize2 = { kGraphSizeX,kGraphSizeY };
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

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos.x = m_NextPos.x;
	}

	m_Pos.y = m_NextPos.y;

	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2), m_Pos.y + (kGraphSizeY / 2) };

	m_Frame++;

	if (m_Frame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX % 4 == 0)
		{
			m_GraphX = 0;
		}
	}

	m_PlayerPos = m_Player->GetPos();

	m_DistancePos = m_Pos - m_PlayerPos;

	if (m_DistancePos.x < 0)
	{
		m_LookEnemy = -1;
	}

	else
	{
		m_LookEnemy = 1;
	}

	m_NextPos = m_Pos;

	(this->*m_func)();

	/*if (m_Pos.y > Game::kScreenHeight)
	{
		m_isDead = true;
	}*/
}

void Enemy1::draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_LookEnemy == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x - kGraphSizeX, m_Pos.y,
				(m_GraphX * 3) * kGraphSizeX, kRectGraphY, kGraphSizeX * 3, 64,
				m_handle, true, true);
		}

		if (m_LookEnemy == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x - kGraphSizeX, m_Pos.y,
				(m_GraphX * 3) * kGraphSizeX, kRectGraphY, kGraphSizeX * 3, 64,
				m_handle, true, false);
		}
	}
}

void Enemy1::UpdatePatrol()
{
	MoveEnemy();

	m_NextPos += m_Vec;

	if (m_DistancePos.x > -500 && m_DistancePos.x < 500)
	{
		m_func = &Enemy1::UpdateDiscovery;
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

	if (m_DistancePos.x > -500 /*+ PlayerGraphSize / 2*/ && m_DistancePos.x < 0/*PlayerGraphSize / 2*/)
	{
		m_Vec.x = 3;
	}

	else if (m_DistancePos.x >= 0/*PlayerGraphSize / 2*/ && m_DistancePos.x < 500/* + PlayerGraphSize / 2*/)
	{
		m_Vec.x = -3;
	}
	else
	{
		m_func = &Enemy1::UpdatePatrol;
	}

	m_NextPos += m_Vec;
}

void Enemy1::updateAttack()
{

}

