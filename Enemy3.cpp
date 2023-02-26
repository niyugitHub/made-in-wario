#include "Enemy3.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include "FallShot.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	// “Š‚°‚½‚à‚Ì‚Ì‘¬“x
	constexpr float kFallSpeed = 15.0f;
	// “Š‚°‚½‚à‚Ì‚Ì‘¬“x’á‰º
	constexpr float kFallSpeedDown = 0.5f;

	// “Š‚°‚é•p“x
	constexpr int kFallFrame = 120;
}

Enemy3::Enemy3() :
	m_FallSpeedX(0),
	m_FallSpeedY(0),
	m_RandThrowFrame(100)
{
	m_Hp = 50;
	m_func = &Enemy3::UpdatePatrol;
}

Enemy3::~Enemy3()
{
}

void Enemy3::update()
{
	if (m_Hp <= 0)
	{
		m_Exist = false;
	}

	if (m_Shot != nullptr)
	{
		if (!m_Shot->GetExist())
		{
			delete m_Shot;
			m_Shot = nullptr;
		}
	}

	BasicMoveEnemy();

	m_NextPos = m_Pos;

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

	m_DistancePos = m_Pos - m_PlayerPos;
	m_DistancePos.x -= static_cast<float>(Player::kSideSize) / 2;

	(this->*m_func)();

	m_PlayerPos = m_Player->GetPos();
	m_NextPos += m_Vec;

	if (!m_CollBottom && !m_CollRight && !m_CollLeft)
	{
	}
	m_Pos = m_NextPos;


	if (m_Shot != nullptr)
	{
		m_Shot->Update();
	}
}

void Enemy3::draw(Vec2 offset)
{
	if (m_Exist)
		DrawBox(m_Pos.x + offset.x, m_Pos.y , m_Pos.x + 50 + offset.x, m_Pos.y + 50, GetColor(0, 0, 255), true);

	/*DrawBox(m_ThrowPos.x, m_ThrowPos.y, m_ThrowPos.x + 50, m_ThrowPos.y + 50,
		GetColor(0, 255, 255), true);*/
	if (m_Shot != nullptr)
	{
		m_Shot->Draw(offset);
	}

//	DrawFormatString(800, 0, GetColor(255, 255, 255), "“G‚ÌÀ•W%f", m_Pos.x);
}

void Enemy3::UpdatePatrol()
{
	if (m_DistancePos.x > -500 && m_DistancePos.x < 500)
	{
		m_func = &Enemy3::UpdateDiscovery;
	}
}

void Enemy3::UpdateDiscovery()
{
	if (m_DistancePos.x < -500 || m_DistancePos.x > 500)
	{
		m_func = &Enemy3::UpdatePatrol;
	}

	if (m_RandThrowFrame <= 0)
	{
		// “Š‚°‚é•p“xƒ‰ƒ“ƒ_ƒ€
		int RandFrame = GetRand(50);

		m_RandThrowFrame = kFallFrame + GetRand(RandFrame);

		m_FallSpeedX = m_DistancePos.x / 60;

		m_Shot = new FallShot(m_Pos,m_FallSpeedX);
	}

	m_RandThrowFrame--;

	/*m_ThrowPos.x += m_Vec.x;

	m_ThrowPos.x -= m_FallSpeedX;
	m_ThrowPos.y -= m_FallSpeedY;

	m_FallSpeedY -= kFallSpeedDown;*/
}

void Enemy3::updateAttack()
{

}
