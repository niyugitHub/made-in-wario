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
	m_Pos(2000,500),
	m_Vec(3,0),
	m_NextPos(0,0),
	m_ThrowPos(0,0),
	m_PlayerPos(0,0),
	m_DistancePos(0,0),
	m_offset(0,0),
	m_Gravity(0),
	m_Hp(30),
	m_HitAttack(false),
	m_KnockBackSpeed(12.0f),
	m_MaxKnockBackSpeed(17.0f),
	m_MoveInverseDirection(1),
	m_MapVec(0,0),
	m_Exist(true),
	m_LookEnemy(1),
	m_GraphX(0),
	m_GraphY(0),
	m_Weight(1.0f),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollLeft(false),
	m_CollRight(false),
	m_TutorialFlag(false),
	m_BossBattle(false),
	m_GameClear(false),
	m_Player(nullptr),
	m_Map(nullptr),
	m_Coll(nullptr)
	/*m_Shot(nullptr)*/
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

bool EnemyBase::StartUpdate()
{
	m_DistancePos = m_CentorPos - m_PlayerPos;

	if (m_offset.x < -Game::kScreenWidth / 2)
	{
		m_offset.x = -Game::kScreenWidth / 2;
	}

	if (m_offset.y < -Game::kScreenHeight / 2)
	{
		m_offset.y = -Game::kScreenHeight / 2;
	}
	if (m_DistancePos.x < Game::kScreenWidth + m_offset.x + 200 && m_DistancePos.x > -Game::kScreenWidth + m_offset.x - 200 &&
		m_DistancePos.y < Game::kScreenHeight + m_offset.y + 200 && m_DistancePos.y > -Game::kScreenHeight + m_offset.y - 200)
	{
		return true;
	}
	return false;
}

void EnemyBase::InitKnockBack()
{
	m_KnockBackSpeed = m_MaxKnockBackSpeed;
}

void EnemyBase::KnockBack()
{
	if (m_KnockBackSpeed > 0)
	{
		if (m_Player->GetPos().x < m_CentorPos.x)
		{
			m_NextPos.x += m_KnockBackSpeed / GetWeight();
			m_KnockBackSpeed -= kKnockBackSpeedDown;
		}

		else if (m_Player->GetPos().x >= m_CentorPos.x)
		{
			m_NextPos.x -= m_KnockBackSpeed / GetWeight();
			m_KnockBackSpeed -= kKnockBackSpeedDown;
		}
	}
}

void EnemyBase::OnDamage(int damage)
{
	m_Hp -= damage;
}

void EnemyBase::OnShotDamage(int damage)
{
	m_Hp -= damage * 2;
}

bool EnemyBase::CollThrow()
{
	// プレイヤーの位置
	float PlayerPosLeft = m_PlayerPos.x + 30;
	float PlayerPosRight = m_PlayerPos.x + 90;
	float PlayerPosUp = m_PlayerPos.y + 10;
	float PlayerPosBottom = m_PlayerPos.y + 118;

	for (auto& Shot : m_Shot)
	{
		if (Shot != nullptr)
		{
			m_ThrowPos = Shot->GetPos();
		}

		else
		{
			continue;
		}

		Vec2 ShotSize1 = Shot->GetShotSize1();
		Vec2 ShotSize2 = Shot->GetShotSize2();

		// エネミーの位置
		float EnemyPosLeft = m_ThrowPos.x + ShotSize1.x;
		float EnemyPosRight = m_ThrowPos.x + ShotSize2.x;
		float EnemyPosUp = m_ThrowPos.y + ShotSize1.y;
		float EnemyPosBottom = m_ThrowPos.y + ShotSize2.y;

		if (PlayerPosLeft > EnemyPosRight) continue;
		if (PlayerPosRight < EnemyPosLeft) continue;
		if (PlayerPosUp > EnemyPosBottom)  continue;
		if (PlayerPosBottom < EnemyPosUp)  continue;

		return true;
	}

	return false;
}

bool EnemyBase::CollShotPlayer()
{
	float ShotPosTop = m_Player->GetShotPos().y;
	float ShotPosBottom = m_Player->GetShotPos().y + 64;
	float ShotPosLeft = m_Player->GetShotPos().x;
	float ShotPosRight = m_Player->GetShotPos().x + 64;

	float EnemyPosLeft = m_Pos.x + GetGraphSize1().x;
	float EnemyPosRight = m_Pos.x + GetGraphSize2().x;
	float EnemyPosUp = m_Pos.y + GetGraphSize1().y;
	float EnemyPosBottom = m_Pos.y + GetGraphSize2().y;

	if (ShotPosRight > EnemyPosRight) return false;
	if (ShotPosRight < EnemyPosLeft) return false;
	if (ShotPosTop > EnemyPosBottom)  return false;
	if (ShotPosBottom < EnemyPosUp)  return false;

	return true;
}
