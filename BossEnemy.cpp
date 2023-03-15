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
	m_Frame(80),
	m_GraphFrame(0),
	m_NowAttack(false)
{
	m_Hp = 1000;
	m_GraphX = 0;
	m_GraphY = 5;
	m_Weight = 100.0f;
	m_GraphSize1 = { 180,250 };
	m_GraphSize2 = { kGraphSizeX - 180,kGraphSizeY - 50 };
	m_func = &BossEnemy::UpdateNotBattle;
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::update()
{
	if (m_Hp <= 0 && m_func != &BossEnemy::UpdateDead)
	{
		m_Exist = false;
		m_GraphY = 9;
		m_GraphX = 0;
		m_Vec.x = 0;
		m_GraphFrame = 0;
		m_func = &BossEnemy::UpdateDead;
	}

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos.x = m_NextPos.x;
	}

	m_Pos.y = m_NextPos.y;

	m_NextPos = m_Pos;

	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2) - 50 , m_Pos.y + kGraphSizeY - 100 };

	m_GraphFrame++;

	if (m_DistancePos.x < 0 && !m_NowAttack)
	{
		m_LookEnemy = -1;
	}

	else if(!m_NowAttack)
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

	if (m_Exist)
	{
		m_PlayerPos = m_Player->GetPos();

		m_DistancePos = m_CentorPos - m_PlayerPos;

	}
	(this->*m_func)();

	m_NextPos += m_Vec;
}

void BossEnemy::draw(Vec2 offset)
{
	if (m_Exist)
	{
	}

	if (m_LookEnemy == 1)
	{
		DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
			m_GraphX * kGraphSizeX, (m_GraphY * kGraphSizeY) + kRectGraphY, kGraphSizeX, kGraphSizeY,
			m_handle, true, true);
	}

	if (m_LookEnemy == -1)
	{
		DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
			m_GraphX * kGraphSizeX, (m_GraphY * kGraphSizeY) + kRectGraphY, kGraphSizeX, kGraphSizeY,
			m_handle, true, false);
	}

	m_offset = offset;
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
	m_Vec.x = 0;

	if (m_DistancePos.x < 500 && m_DistancePos.x > -500)
	{
		m_BossBattle = true;
	}

	if (m_BossBattle)
	{
		m_func = &BossEnemy::UpdateDiscovery;
	}
}

void BossEnemy::UpdateDiscovery()
{
	m_Frame--;
	m_GraphY = 2;

	m_GraphSize1 = { 180,250 };
	m_GraphSize2 = { kGraphSizeX - 180,kGraphSizeY - 50 };

	if (m_DistancePos.x < 0)
	{
		m_Vec.x = kSpeed;
	}

	if (m_DistancePos.x >= 0)
	{
		m_Vec.x = -kSpeed;
	}

	ChangeGraph(5);

	if (m_DistancePos.x < 200 && m_DistancePos.x > -200 && m_Frame <= 0)
	{
		m_Frame = 50 + GetRand(50);
		int RandAttack = GetRand(3);

		if (RandAttack == 0)
		{
			m_func = &BossEnemy::UpdateAttack1;
			m_GraphFrame = 0;
			m_GraphX = 0;
			m_GraphY = 3;
			m_Vec.x = 0;
			m_NowAttack = true;
		}
		if (RandAttack == 1)
		{
			m_func = &BossEnemy::UpdateAttack2;
			m_GraphFrame = 0;
			m_GraphX = 0;
			m_GraphY = 6;
			m_Vec.x = 0;
			m_NowAttack = true;
		}
		if (RandAttack == 2)
		{
			m_func = &BossEnemy::UpdateAttack3;
			m_GraphFrame = 0;
			m_GraphX = 0;
			m_GraphY = 1;
			m_Vec.x = 0;
			m_NowAttack = true;
		}
	}
}

void BossEnemy::UpdateAttack1()
{
	if (m_GraphFrame >= 40 && m_GraphFrame % 5 == 0)
	{
		if (m_LookEnemy == -1 && m_GraphFrame <= 50)
		{
			m_GraphSize1 = { 180,250 };
			m_GraphSize2 = { kGraphSizeX - 30,kGraphSizeY - 50 };
		}

		else if (m_LookEnemy == 1 && m_GraphFrame <= 50)
		{
			m_GraphSize1 = { 50,250 };
			m_GraphSize2 = { kGraphSizeX - 180,kGraphSizeY - 50 };
		}

		else
		{
			m_GraphSize1 = { 180,250 };
			m_GraphSize2 = { kGraphSizeX - 180,kGraphSizeY - 50 };
		}

		m_GraphX++;
		if (m_GraphX >= 9)
		{
			m_GraphX = 0;
		}
	}

	if (m_GraphFrame >= 60 && m_GraphX == 0)
	{
		m_func = &BossEnemy::UpdateDiscovery;
		m_NowAttack = false;
	}
}

void BossEnemy::UpdateAttack2()
{
	if (m_GraphFrame >= 40 && m_GraphFrame % 5 == 0)
	{
		m_GraphSize1 = { 50,400 };
		m_GraphSize2 = { kGraphSizeX - 30,kGraphSizeY - 50 };

		m_GraphX++;
		if (m_GraphX >= 9)
		{
			m_GraphX = 0;
		}
	}

	if (m_GraphFrame >= 60 && m_GraphX == 0)
	{
		m_func = &BossEnemy::UpdateDiscovery;
		m_NowAttack = false;
	}
}

void BossEnemy::UpdateAttack3()
{
	if (m_GraphFrame >= 60 && m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 8)
		{
			m_GraphX = 0;
		}

		if (m_LookEnemy == -1)
		{
			m_Vec.x = kSpeed * 3.0f;
		}

		if (m_LookEnemy == 1)
		{
			m_Vec.x = -kSpeed * 3.0f;
		}
	}


	if (m_GraphFrame >= 180)
	{
		m_func = &BossEnemy::UpdateDiscovery;
		m_NowAttack = false;
	}

	if (m_CollLeft || m_CollRight)
	{
		m_func = &BossEnemy::UpdateDiscovery;
		m_NowAttack = false;
	}
}

void BossEnemy::UpdateAttack4()
{
}

void BossEnemy::UpdateDead()
{
	if (m_GraphFrame % 8 == 0)
	{
		m_GraphX++;
		if (m_GraphX >= 5)
		{
			m_GraphX = 5;
		}
		if (m_GraphFrame >= 100)
		{
			m_BossBattle = false;
		}
	}
}
