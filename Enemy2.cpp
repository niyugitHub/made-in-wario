#include "Enemy2.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr float kPlayerGraphSize = 100.0f;
	
	// プレイヤーを追いかけるときの速度
	constexpr float kMoveChaseFly = 0.15f;
	constexpr float kMoveChaseField = 0.15f;

	// 通常時の速度
	constexpr float kMoveFly = 0.05f;
}

Enemy2::Enemy2() : 
	m_Frame(35),
	m_FlySpeed(-kMoveFly),
	m_FieldSpeed(0.0f)
{
	m_func = &Enemy2::UpdatePatrol;
}

Enemy2::~Enemy2()
{
}

void Enemy2::update()
{
	m_PlayerPos = m_Player->GetPos();
	m_NextPos = m_Pos;

	(this->*m_func)();

	m_DistancePos = m_Pos - m_PlayerPos;

	if (m_DistancePos.x > -500 && m_DistancePos.x < 500)
	{
		m_func = &Enemy2::UpdateDiscovery;
	}
}

void Enemy2::draw()
{
	if (m_Exist)
		DrawBox(m_Pos.x, m_Pos.y, m_Pos.x + 50, m_Pos.y + 50, GetColor(0, 255, 0), true);
}

void Enemy2::UpdatePatrol()
{
	BasicMoveEnemy();
	m_Pos += m_Vec;

	if (m_CollBottom)
	{
		m_FlySpeed *= -1;
	}

	m_Frame++;

	if (m_Frame % 70 == 0)
	{
		m_FlySpeed *= -1;
	}

	m_Vec.y += m_FlySpeed;

	if (m_Vec.y >= 3)
		m_Vec.y = 3;

	if (m_Vec.y <= -3)
		m_Vec.y = -3;

	m_NextPos += m_Vec;

	m_Pos = m_NextPos;
	/*if (!m_CollBottom && !m_CollTop)
	{
	}
	else
	{
		m_FlySpeed *= -1;
		m_Frame = 35;
	}*/

	//m_Vec.x += 3;
	//if (m_FieldSpeed < 3)
	//{
	//	m_FieldSpeed += kMoveFly;
	//}

	//if (m_DistancePos.x >= kPlayerGraphSize / 2 && m_DistancePos.x < 500 + kPlayerGraphSize / 2)
	//{
	//	//	m_Vec.x -= 3;
	//	if (m_FieldSpeed > -3)
	//	{
	//		m_FieldSpeed -= kMoveFly;
	//	}
	//}
}

void Enemy2::UpdateDiscovery()
{
	BasicMoveEnemy();

	m_Pos += m_Vec;
	if (m_DistancePos.x > -500 && m_DistancePos.x < 0)
	{
		//m_Vec.x += 3;
		if (m_FieldSpeed < 3)
		{
			m_FieldSpeed += kMoveChaseField;
		}
	}

	if (m_DistancePos.x >= kPlayerGraphSize / 2 && m_DistancePos.x < 500 + kPlayerGraphSize / 2)
	{
	//	m_Vec.x -= 3;
		if (m_FieldSpeed > -3)
		{
			m_FieldSpeed -= kMoveChaseField;
		}
	}
	
	if(m_DistancePos.x < -500 || m_DistancePos.x > 500 + kPlayerGraphSize / 2)
	{
		m_FlySpeed = -kMoveFly;
		m_Frame = 35;
		m_Vec.y = 0;
		m_func = &Enemy2::UpdatePatrol;
	}

	m_Vec.x += m_FieldSpeed;

	if (m_DistancePos.y > kPlayerGraphSize / 2)
	{
		if(m_FlySpeed > -3)
			m_FlySpeed -= kMoveChaseFly;
	}

	if (m_DistancePos.y <= kPlayerGraphSize / 2)
	{
		if (m_FlySpeed < 3)
			m_FlySpeed += kMoveChaseFly;
	}

	m_Vec.y = m_FlySpeed;

	if (m_CollBottom)
	{
		m_FlySpeed = 0;
		m_Pos.y += 1;
	}

	m_NextPos += m_Vec;

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos.x = m_NextPos.x;
	}
}

void Enemy2::updateAttack()
{
}
