#include "BossEnemy.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr float kPlayerGraphSize = 100.0f;

	// 画像のサイズ
	constexpr float kGraphSizeX = 480.0f;
	constexpr float kGraphSizeY = 480.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 622;
	constexpr int kRectGraphX = 122;

	// 移動速度(通常)
	constexpr float kSpeed = 3.0f;

	// 移動速度(ダッシュ時)
	constexpr float kDashSpeed = 6.0f;
}

BossEnemy::BossEnemy() :
	m_Frame(200),
	m_GraphFrame(0)
{
	m_Hp = 1000;
	m_GraphX = 0;
	m_GraphY = 5;
	m_GraphSize = { kGraphSizeX,kGraphSizeY };
	m_func = &BossEnemy::UpdateNotBattle;
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::update()
{
	if (m_Hp <= 0)
	{
		m_Exist = false;
	}

	m_GraphFrame++;

	if (m_DistancePos.x < 0)
	{
		m_LookEnemy = -1;
	}

	else
	{
		m_LookEnemy = 1;
	}

	if (m_Exist)
	{
		m_PlayerPos = m_Player->GetPos();

		if (!m_CollLeft && !m_CollRight)
		{
			m_Pos.x = m_NextPos.x;
		}

		m_Pos.y = m_NextPos.y;

		m_NextPos = m_Pos;

		m_DistancePos = m_Pos - m_PlayerPos;

		(this->*m_func)();
	}
}

void BossEnemy::draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_LookEnemy == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y - kGraphSizeY / 2,
				m_GraphX * kGraphSizeX, (m_GraphY * kGraphSizeY) + kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, true);
		}

		if (m_LookEnemy == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y - kGraphSizeY / 2,
				m_GraphX * kGraphSizeX, (m_GraphY * kGraphSizeY) + kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, false);
		}
	}
}

void BossEnemy::ChangeGraph(int i)
{
	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;
		if (m_GraphX >= i)
		{
			m_GraphX = 0;
		}
	}
}

void BossEnemy::UpdateNotBattle()
{
	ChangeGraph(6);

	if (m_DistancePos.x < 500 && m_DistancePos.x > -500)
	{
		m_StartBattle = true;
	}

	if (m_StartBattle)
	{
		m_func = &BossEnemy::UpdateDiscovery;
	}
}

void BossEnemy::UpdateDiscovery()
{
	m_GraphY = 2;

	if (m_DistancePos.x < 0)
	{
		m_Vec.x = kSpeed;
	}

	if (m_DistancePos.x >= 0)
	{
		m_Vec.x = -kSpeed;
	}

	ChangeGraph(5);

	m_NextPos += m_Vec;

	if (m_DistancePos.x < 200 && m_DistancePos.x > -200)
	{
		int RandAttack = /*GetRand(4)*/0;

		if (RandAttack == 0)
		{
			m_func = &BossEnemy::UpdateAttack1;
			m_GraphFrame = 0;
			m_GraphX = 0;
			m_GraphY = 3;
		}
		if (RandAttack == 1)
		{
			m_func = &BossEnemy::UpdateAttack2;
		}
		if (RandAttack == 2)
		{
			m_func = &BossEnemy::UpdateAttack3;
		}
		if (RandAttack == 3)
		{
			m_func = &BossEnemy::UpdateAttack4;
		}
	}
}

void BossEnemy::UpdateAttack1()
{
	if (m_GraphFrame >= 60 && m_GraphFrame % 5 == 0)
	{
		m_GraphX++;
		if (m_GraphX >= 9)
		{
			m_GraphX = 0;
		}
	}

	if (m_GraphFrame >= 60 && m_GraphX == 0)
	{
		m_func = &BossEnemy::UpdateDiscovery;
	}
}

void BossEnemy::UpdateAttack2()
{
}

void BossEnemy::UpdateAttack3()
{
}

void BossEnemy::UpdateAttack4()
{
}
