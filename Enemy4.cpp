#include "Enemy4.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr float kPlayerGraphSize = 100.0f;

	// ジャンプ力
	constexpr float kJumpPower = 30.0f;
	// 重力
	constexpr float kGravtiy = 1.5f;
	// 移動スピード
	constexpr float kSpeed = 5.0f;
	// ジャンプ間隔
	constexpr int kJumpFrame = 30;

	// 画像のサイズ
	constexpr float kGraphSizeX = 64.0f;
	constexpr float kGraphSizeY = 64.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 64;
	constexpr int kRectGraphX = 64;
}

Enemy4::Enemy4() :
	m_JumpPower(0),
	m_JumpFrame(0),
	m_Speed(-kSpeed)
{
	m_GraphX = 0;
	m_GraphY = 1;
	m_Weight = 1.5f;
	m_Hp = 50;
	m_GraphSize2 = { 0,0 };
	m_GraphSize2 = { kGraphSizeX,kGraphSizeY };
	m_func = &Enemy4::NotUpdate;
}

Enemy4::~Enemy4()
{
}

void Enemy4::update()
{
	if (m_Hp <= 0)
	{
		m_Exist = false;
	}
	m_PlayerPos = m_Player->GetPos();


	if (!m_CollLeft && m_Pos.x > m_NextPos.x)
	{
		m_Pos.x = m_NextPos.x;
	}

	if (!m_CollRight && m_Pos.x < m_NextPos.x)
	{
		m_Pos.x = m_NextPos.x;
	}

	m_Pos.y = m_NextPos.y;

	m_NextPos = m_Pos;

	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2), m_Pos.y + (kGraphSizeY / 2) };

	(this->*m_func)();
}

void Enemy4::draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_LookEnemy == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, m_GraphY * kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, true);
		}

		if (m_LookEnemy == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, m_GraphY * kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, false);
		}
	}
	m_offset = offset;
}

void Enemy4::UpdateGraph()
{
	if (m_JumpPower < -25)	m_GraphX = 1;
	else if (m_JumpPower < -17)	m_GraphX = 2;
	else if (m_JumpPower < -5)	m_GraphX = 3;
	else if (m_JumpPower < 5)	m_GraphX = 4;
	else if (m_JumpPower < 15)	m_GraphX = 5;
	else if (m_JumpPower < 25)	m_GraphX = 6;
	else if (m_JumpPower < 30)	m_GraphX = 7;
}

void Enemy4::NotUpdate()
{
	if (StartUpdate())
	{
		m_func = &Enemy4::UpdatePatrol;
	}
}

void Enemy4::UpdatePatrol()
{
	UpdateGraph();

	if (m_CollBottom)
	{
		m_GraphX = 0;
		m_JumpPower = 0;
		m_JumpFrame++;
		m_Vec.x = 0;
	}

	if (m_CollTop)
	{
		m_JumpPower = 1;
	}

	if (m_CollLeft)
	{
		m_Speed = kSpeed;
		m_Vec.x = m_Speed;
		m_LookEnemy = -1;
	}

	if (m_CollRight)
	{
		m_Speed = -kSpeed;
		m_Vec.x = m_Speed;
		m_LookEnemy = 1;
	}

	if (m_JumpFrame >= kJumpFrame)
	{
		m_JumpPower = -kJumpPower;
		m_JumpFrame = 0;
		m_Vec.x = m_Speed;
	}

	m_Vec = { m_Vec.x ,m_JumpPower };
	if (m_JumpPower < kJumpPower)
	{
		m_JumpPower += kGravtiy;
	}

	m_NextPos += m_Vec;
}
