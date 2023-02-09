#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include "Collision.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr float kKnockBackSpeedDown = 0.3f;
}

EnemyBase::EnemyBase() : 
	m_Pos(1600,500),
	m_Vec(3,0),
	m_NextPos(0,0),
	m_PlayerPos(0,0),
	m_DistancePos(0,0),
	m_Gravity(0),
	m_Hp(30),
	m_HitAttack(false),
	m_KnockBackSpeed(12.0f),
	m_MaxKnockBackSpeed(12.0f),
	m_MoveInverseDirection(1),
	m_MapVec(0,0),
	m_Exist(true),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollLeft(false),
	m_CollRight(false),
	m_Player(nullptr),
	m_Map(nullptr),
	m_Coll(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::end()
{
}

void EnemyBase::update()
{

}

void EnemyBase::draw()
{
	if(m_Exist)
	DrawBox(m_Pos.x, m_Pos.y, m_Pos.x + 50,m_Pos.y + 50,GetColor(255, 0, 0), true);
}

void EnemyBase::MoveEnemy()
{
	m_Vec.x = -3;

	m_MapVec = m_Map->GetVec();


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

	if (m_CollLeft || m_CollRight)
	{
		m_MoveInverseDirection *= -1;
	}

	m_Vec.x *= m_MoveInverseDirection;

	m_Vec.x += m_MapVec.x;

//	m_Pos += m_Vec;
}

void EnemyBase::BasicMoveEnemy()
{
	m_Vec.x = 0;
	m_MapVec = m_Map->GetVec();


	/*if (!m_CollBottom)
	{
		m_Gravity += kGravity;
		m_Vec.y += m_Gravity;
	}*/

	if(m_CollBottom)
	{
		m_Gravity = 0;
		m_Vec.y = 0;
	}

	m_Vec.x *= m_MoveInverseDirection;

	m_Vec.x += m_MapVec.x;
}

void EnemyBase::InitKnockBack()
{
	m_KnockBackSpeed = m_MaxKnockBackSpeed;
}

void EnemyBase::KnockBack()
{
	if (m_KnockBackSpeed > 0)
	{
		if (m_Player->GetPos().x < m_Pos.x)
		{
			m_Pos.x += m_KnockBackSpeed;
			m_KnockBackSpeed -= kKnockBackSpeedDown;
		}

		else if (m_Player->GetPos().x >= m_Pos.x)
		{
			m_Pos.x -= m_KnockBackSpeed;
			m_KnockBackSpeed -= kKnockBackSpeedDown;
		}
	}
}
