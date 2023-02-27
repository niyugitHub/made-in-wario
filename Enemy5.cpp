#include "Enemy5.h"
#include "EnemyBase.h"
#include "HomingShot.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr float kPlayerGraphSize = 100.0f;

	// プレイヤーを追いかけるときの速度
	constexpr float kMoveChaseFly = 0.2f;
	constexpr float kMoveChaseField = 0.2f;

	// プレイヤーを追いかけるときの最大速度
	constexpr float kMoveChaseMax= 4.0f;

	// 通常時の速度
	constexpr float kMoveFly = 0.05f;

	// ショットを打つまでのフレーム
	constexpr int kShotFrame = 40;
	constexpr int kNextShotFrame = 180;

	// ショットのスピード
	constexpr float kShotSpeed = 10.0f;
}

Enemy5::Enemy5() :
	m_Frame(35),
	m_ShotFrame(0),
	m_NextShotFrame(kNextShotFrame),
	m_FlySpeed(-kMoveFly),
	m_FieldSpeed(0.0f)
{
	m_Hp = 50;
	m_func = &Enemy5::UpdatePatrol;
}

Enemy5::~Enemy5()
{
}

void Enemy5::update()
{
	if (m_Hp <= 0)
	{
		m_Exist = false;
	}
	m_PlayerPos = m_Player->GetPos();
	m_NextPos = m_Pos;

	(this->*m_func)();

	m_DistancePos = m_Pos - m_PlayerPos;

	if (m_Shot != nullptr)
	{
		m_Shot->Update();
		if (!m_Shot->GetExist())
		{
			delete m_Shot;
			m_Shot = nullptr;
		}
	}


	/*if (m_DistancePos.x > -500 && m_DistancePos.x < 500 &&
		m_DistancePos.y > -500 && m_DistancePos.y < 500)
	{
		m_func = &Enemy5::UpdateDiscovery;
	}*/
}

void Enemy5::draw(Vec2 offset)
{
	if (m_Exist)
	{
		DrawBox(m_Pos.x + offset.x,
			m_Pos.y, m_Pos.x + 50 + offset.x,
			m_Pos.y + 50, GetColor(0, 255, 0), true);
	}

	if (m_Shot != nullptr)
	{
		m_Shot->Draw(offset);
	}
}

void Enemy5::UpdatePatrol()
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

	if (m_DistancePos.x > -500 && m_DistancePos.x < 500 &&
		m_DistancePos.y > -500 && m_DistancePos.y < 500)
	{
		m_func = &Enemy5::UpdateDiscovery;
	}
}

void Enemy5::UpdateDiscovery()
{
	m_NextShotFrame++;
	m_ShotFrame--;
	if(m_ShotFrame <= 0)
	{
		BasicMoveEnemy();

		m_Pos += m_Vec;
		if (m_DistancePos.x < kPlayerGraphSize / 2)
		{
			//m_Vec.x += 3;
			if (m_FieldSpeed < kMoveChaseMax)
			{
				m_FieldSpeed += kMoveChaseField;
			}
		}

		if (m_DistancePos.x >= kPlayerGraphSize / 2)
		{
			//	m_Vec.x -= 3;
			if (m_FieldSpeed > -kMoveChaseMax)
			{
				m_FieldSpeed -= kMoveChaseField;
			}
		}


		if (m_DistancePos.x > -500 && m_DistancePos.x < 500 &&
			m_DistancePos.y > -500 && m_DistancePos.y < 500 && m_NextShotFrame >= kNextShotFrame)
		{
			m_ShotFrame = 0;
			m_func = &Enemy5::UpdateAttackShot;
		}

		m_Vec.x += m_FieldSpeed;

		if (m_DistancePos.y > kPlayerGraphSize / 2)
		{
			if (m_FlySpeed > -kMoveChaseMax)
				m_FlySpeed -= kMoveChaseFly;
		}

		if (m_DistancePos.y <= kPlayerGraphSize / 2)
		{
			if (m_FlySpeed < kMoveChaseMax)
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
}

void Enemy5::UpdateAttackShot()
{
	m_ShotFrame++;

	if (m_ShotFrame >= kShotFrame)
	{
		m_NextShotFrame = 0;

		Vec2 PlayerPos = { m_PlayerPos.x + (Player::kSideSize / 2) ,m_PlayerPos.y + Player::kColumnSize / 2 };
		Vec2 vel = m_Pos - PlayerPos;

		vel = vel.normalize();
		vel *= -kShotSpeed;

		m_Shot = new HomingShot(m_Pos, vel);
		m_func = &Enemy5::UpdateDiscovery;
	}
}
