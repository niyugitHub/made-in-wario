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

	// 画像のサイズ
	constexpr float kGraphSizeX = 71.2f;
	constexpr float kGraphSizeY = 64.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 0;
}

Enemy2::Enemy2() : 
	m_Frame(35),
	m_GraphFrame(0),
	m_FlySpeed(-kMoveFly),
	m_FieldSpeed(0.0f)
{
	m_GraphX = 0;
	m_GraphY = 0;
	m_Hp = 50;
	m_GraphSize1 = { 0,0 };
	m_GraphSize2 = { kGraphSizeX,kGraphSizeY };
	m_func = &Enemy2::UpdatePatrol;
}

Enemy2::~Enemy2()
{
}

void Enemy2::update()
{
	if (m_Hp <= 0)
	{
		m_Exist = false;
	}

	/*if (!m_CollRight && !m_CollLeft)
	{
		m_Pos.x = m_NextPos.x;
	}*/

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

	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2), m_Pos.y + (kGraphSizeY / 2) };

	if (m_Exist)
	{
		m_GraphFrame++;

		if (m_GraphFrame % 5 == 0)
		{
			m_GraphX++;

			if (m_GraphX % 4 == 0)
			{
				m_GraphX = 0;
			}
		}

		if (m_DistancePos.x < 0)
		{
			m_LookEnemy = -1;
		}

		else
		{
			m_LookEnemy = 1;
		}

		m_PlayerPos = m_Player->GetPos();

		(this->*m_func)();

		m_DistancePos = m_CentorPos - m_PlayerPos;

		if (m_DistancePos.x > -500 && m_DistancePos.x < 500)
		{
			m_func = &Enemy2::UpdateDiscovery;
		}
	}
}

void Enemy2::draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_LookEnemy == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				(m_GraphX * 4) * kGraphSizeX, kRectGraphY, kGraphSizeX + 10 , kGraphSizeY,
				m_handle, true, true);
		}

		if (m_LookEnemy == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				(m_GraphX * 4) * kGraphSizeX, kRectGraphY, kGraphSizeX + 10, kGraphSizeY,
				m_handle, true, false);
		}
	}

//#ifdef _DEBUG
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "敵の体力%d", m_Hp);
//#endif
}

void Enemy2::UpdatePatrol()
{
	BasicMoveEnemy();
	
	if (m_CollBottom)
	{
		m_FlySpeed *= -1;
		m_Frame = 0;
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
}

void Enemy2::UpdateDiscovery()
{
	BasicMoveEnemy();

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

	m_NextPos += m_Vec;
}

void Enemy2::updateAttack()
{
}
