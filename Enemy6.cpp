#include "Enemy6.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr int PlayerGraphSize = 100;

	// 画像のサイズ
	constexpr float kGraphSizeX = 333.0f;
	constexpr float kGraphSizeY = 333.0f;

	// 画像のどこから始まるか
	constexpr float kGraphStartX = 0.0f;
	constexpr float kGraphStartY = 5400.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 0;
	constexpr int kRectGraphX = 0;

	// 敵のスピード
	constexpr float kSpeed = 7.0f;
}

Enemy6::Enemy6() : 
	m_GraphFrame(0),
	m_NowAttack(false)
{
	m_GraphX = 0;
	m_GraphY = 0;
	m_Hp = 180;
	m_GraphSize1 = { 105,170 };
	m_GraphSize2 = { 215,kGraphSizeY - 70 };
	m_func = &Enemy6::NotUpdate;
	m_Vec = { 0,0 };
	m_Weight = 3.0f;
}

Enemy6::~Enemy6()
{
}

void Enemy6::update()
{
	if (m_Hp <= 0)
	{
		m_Exist = false;
	}

	if (!m_CollRight && m_Pos.x < m_NextPos.x)
	{
		m_Pos.x = m_NextPos.x;
	}

	if (!m_CollLeft && m_Pos.x > m_NextPos.x)
	{
		m_Pos.x = m_NextPos.x;
	}

	if (!m_CollTop)
	{
		m_Pos.y = m_NextPos.y;
	}

	m_NextPos = m_Pos;

	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2) - 30, m_Pos.y + (kGraphSizeY / 2) };

	m_GraphFrame++;

	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;
	}

	m_PlayerPos = m_Player->GetPos();

	m_DistancePos = m_CentorPos - m_PlayerPos;

	if (m_DistancePos.x < 0 && !m_NowAttack)
	{
		m_LookEnemy = -1;
	}

	else if (!m_NowAttack)
	{
		m_LookEnemy = 1;
	}


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

	(this->*m_func)();

	m_NextPos += m_Vec;
}

void Enemy6::draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_LookEnemy == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, kGraphStartY + (m_GraphY * kGraphSizeY), kGraphSizeX, kGraphSizeY,
				m_handle, true, true);
		}

		if (m_LookEnemy == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, kGraphStartY + (m_GraphY * kGraphSizeY), kGraphSizeX, kGraphSizeY,
				m_handle, true, false);
		}
	}
	m_offset = offset;
}

void Enemy6::NotUpdate()
{
	if (StartUpdate())
	{
		m_func = &Enemy6::UpdatePatrol;
	}
}

void Enemy6::UpdatePatrol()
{
	if (m_GraphX >= 9)
	{
		m_GraphX = 0;
	}

	if (m_DistancePos.x > -500 && m_DistancePos.x < 500 &&
		m_DistancePos.y > -200 && m_DistancePos.y < 300)
	{
		m_func = &Enemy6::UpdateDiscovery;
		m_GraphY = 1;
	}
}

void Enemy6::UpdateDiscovery()
{
	BasicMoveEnemy();

	m_GraphSize1 = { 105,170 };
	m_GraphSize2 = { 215,kGraphSizeY - 70 };

	if (m_GraphX >= 5)
	{
		m_GraphX = 0;
	}

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

	if (m_DistancePos.x < 0)
	{
		m_Vec.x = kSpeed;
	}

	else if (m_DistancePos.x >= 0)
	{
		m_Vec.x = -kSpeed;
	}
	
	if (m_DistancePos.x < -1000 || m_DistancePos.x > 1000 ||
		m_DistancePos.y < -200 || m_DistancePos.y > 300)
	{
		m_func = &Enemy6::UpdatePatrol;
		m_GraphY = 0;
		m_Vec.x = 0;
	}

	if (m_DistancePos.x < 180 && m_DistancePos.x > -120)
	{
		m_GraphFrame = 0;
		m_func = &Enemy6::UpdateAttack;
		m_NowAttack = true;
		m_Vec.x = 0;
		m_GraphY = 2;
		m_GraphX = 0;
	}
}

void Enemy6::UpdateAttack()
{
	if (m_LookEnemy == -1 && m_GraphX >= 9)
	{
		m_GraphSize1 = { 105,70 };
		m_GraphSize2 = { 333,kGraphSizeY - 70 };
	}

	else if (m_LookEnemy == 1 && m_GraphX >= 9)
	{
		m_GraphSize1 = { 0,70 };
		m_GraphSize2 = { 215,kGraphSizeY - 70 };
	}

	else
	{
		m_GraphSize1 = { 105,170 };
		m_GraphSize2 = { 215,kGraphSizeY - 70 };
	}

	if (m_GraphX >= 11)
	{
		m_func = &Enemy6::UpdateDiscovery;
		m_NowAttack = false;
		m_GraphX = 0;
		m_GraphY = 1;
	}
}
