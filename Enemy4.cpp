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
	constexpr float kSpeed = 5;
	// ジャンプ間隔
	constexpr int kJumpFrame = 30;
}

Enemy4::Enemy4() : 
	m_JumpPower(0),
	m_JumpFrame(0),
	m_Speed(kSpeed)
{
	m_Hp = 50;
	m_func = &Enemy4::UpdatePatrol;
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
	m_NextPos = m_Pos;

	(this->*m_func)();
}

void Enemy4::draw(Vec2 offset)
{
	if (m_Exist)
	{
		DrawBox(m_Pos.x + offset.x,
			m_Pos.y, m_Pos.x + 50 + offset.x,
			m_Pos.y + 50, 
			GetColor(0, 255, 0), true);
	}
}

void Enemy4::UpdatePatrol()
{
	if (m_CollBottom)
	{
		m_JumpPower = 0;
		m_JumpFrame++;
		m_Vec.x = 0;
	}

	if (m_JumpFrame >= kJumpFrame)
	{
		m_JumpPower = -kJumpPower;
		m_JumpFrame = 0;
		m_Vec.x = m_Speed;
	}

	m_Vec = { m_Vec.x ,m_JumpPower };
	if (m_JumpPower < 50)
	{
		m_JumpPower += kGravtiy;
	}



	if (m_CollLeft || m_CollRight)
	{
		m_Speed *= -1;
	}


	m_NextPos += m_Vec;

	m_Pos = m_NextPos;
}
