#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include "Collision.h"
#include "ShotBase.h"
#include "FallShot.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr float kKnockBackSpeedDown = 1.0f;
}

EnemyBase::EnemyBase() : 
	m_Pos(1600,500),
	m_Vec(3,0),
	m_NextPos(0,0),
	m_ThrowPos(0,0),
	m_PlayerPos(0,0),
	m_DistancePos(0,0),
	m_Gravity(0),
	m_Hp(30),
	m_HitAttack(false),
	m_KnockBackSpeed(12.0f),
	m_MaxKnockBackSpeed(17.0f),
	m_MoveInverseDirection(1),
	m_MapVec(0,0),
	m_Exist(true),
	m_LookEnemy(1),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollLeft(false),
	m_CollRight(false),
	m_Player(nullptr),
	m_Map(nullptr),
	m_Coll(nullptr),
	m_Shot(nullptr)
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

void EnemyBase::draw(Vec2 offset)
{
	if (m_Exist)
	{
		DrawBox(m_Pos.x + offset.x, m_Pos.y,
			m_Pos.x + 50 + offset.x,m_Pos.y + 50,GetColor(255, 0, 0), true);
	}


#ifdef _DEBUG
//	DrawFormatString(0, 100, GetColor(255, 255, 255), "敵の体力%d", m_Hp);
//	DrawFormatString(0, 100, GetColor(255, 255, 255), "offset.x%f", offset.x);
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "Vec.x%f", m_Vec.x);
//	DrawFormatString(300, 0, GetColor(255, 255, 255), "Pos.x%f", m_Pos.x);
//	DrawFormatString(900, 0, GetColor(255, 255, 255), "PlayerPos.x%f", m_PlayerPos.x);
//	DrawFormatString(600, 100, GetColor(255, 255, 255), "DistancePos.x%f", m_DistancePos.x);
#endif
}

void EnemyBase::MoveEnemy()
{
	m_Vec.x = -3;

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

	/*m_Vec.x += m_MapVec.x;*/

//	m_Vec.x += m_MapVec.x;

//	m_Pos += m_Vec;
}

void EnemyBase::BasicMoveEnemy()
{
	m_Vec.x = 0;
//	m_MapVec = m_Map->GetVec();


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

//	m_Vec.x *= m_MoveInverseDirection;
//	m_Vec.x += m_MapVec.x;
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

void EnemyBase::OnDamage(int damage)
{
	m_Hp -= damage;
}

bool EnemyBase::CollThrow()
{
	// プレイヤーの位置
	float PlayerPosLeft = m_PlayerPos.x + 30;
	float PlayerPosRight = m_PlayerPos.x + 90;
	float PlayerPosUp = m_PlayerPos.y + 10;
	float PlayerPosBottom = m_PlayerPos.y + 118;

	if (m_Shot != nullptr)
	{
		m_ThrowPos = m_Shot->GetPos();
	}

	else	return false;

	// エネミーの位置
	float EnemyPosLeft = m_ThrowPos.x;
	float EnemyPosRight = m_ThrowPos.x + 50;
	float EnemyPosUp = m_ThrowPos.y;
	float EnemyPosBottom = m_ThrowPos.y + 50;

	if (PlayerPosLeft > EnemyPosRight) return false;
	if (PlayerPosRight < EnemyPosLeft) return false;
	if (PlayerPosUp > EnemyPosBottom)  return false;
	if (PlayerPosBottom < EnemyPosUp)  return false;

	return true;
}

bool EnemyBase::CollShotPlayer()
{
	float ShotPosTop = m_Player->GetShotPos().y;
	float ShotPosBottom = m_Player->GetShotPos().y + 50;
	float ShotPosLeft = m_Player->GetShotPos().x;
	float ShotPosRight = m_Player->GetShotPos().x + 50;

	float EnemyPosLeft = m_Pos.x;
	float EnemyPosRight = m_Pos.x + 50;
	float EnemyPosUp = m_Pos.y;
	float EnemyPosBottom = m_Pos.y + 50;

	if (ShotPosRight > EnemyPosRight) return false;
	if (ShotPosRight < EnemyPosLeft) return false;
	if (ShotPosTop > EnemyPosBottom)  return false;
	if (ShotPosBottom < EnemyPosUp)  return false;

	return true;
}
