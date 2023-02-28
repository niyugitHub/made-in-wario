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

	// ‰æ‘œ‚ÌƒTƒCƒY
	constexpr float kGraphSizeX = 125.0f;
	constexpr float kGraphSizeY = 100.0f;

	// ‰æ‘œ‚Ì’ZŒa•”•ª•\Ž¦
	constexpr int kRectGraphX = 125;
	constexpr int kRectGraphY = 422;
}

Enemy3::Enemy3() :
	m_GraphFrame(0),
	m_FallSpeedX(0),
	m_FallSpeedY(0),
	m_RandThrowFrame(100)
{
	m_Hp = 50;
	m_GraphX = 0;
	m_GraphY = 0;
	m_GraphSize = { kGraphSizeX,kGraphSizeY };
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

	m_GraphFrame++;

	if (m_Shot != nullptr)
	{
		if (!m_Shot->GetExist())
		{
			delete m_Shot;
			m_Shot = nullptr;
		}
	}

	if (m_Exist)
	{
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

		if (m_DistancePos.x < 0)
		{
			m_LookEnemy = -1;
		}

		else
		{
			m_LookEnemy = 1;
		}

		m_DistancePos.x -= static_cast<float>(Player::kSideSize) / 2;

		(this->*m_func)();

		m_PlayerPos = m_Player->GetPos();
		m_NextPos += m_Vec;

		if (!m_CollBottom && !m_CollRight && !m_CollLeft)
		{
		}
		m_Pos = m_NextPos;
	}


	if (m_Shot != nullptr)
	{
		m_Shot->Update();
	}
}

void Enemy3::draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_LookEnemy == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y,
				m_GraphX * kGraphSizeX, (m_GraphY * kGraphSizeY) + kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, true);
		}

		if (m_LookEnemy == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y,
				m_GraphX * kGraphSizeX, (m_GraphY * kGraphSizeY) + kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, false);
		}
	}

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
	m_GraphY = 0;
	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 9)
		{
			m_GraphX = 0;
		}
	}

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

	if (m_RandThrowFrame == 50)
	{
		m_GraphY = 1;
		m_GraphX = 0;
	}

	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 13 && m_GraphY == 1)
		{
			m_GraphX = 0;
		}
		if (m_GraphX >= 9 && m_GraphY == 0)
		{
			m_GraphX = 0;
		}
	}

	if (m_RandThrowFrame <= 0)
	{
		// “Š‚°‚é•p“xƒ‰ƒ“ƒ_ƒ€
		int RandFrame = GetRand(50);

		m_RandThrowFrame = kFallFrame + GetRand(RandFrame);

		m_FallSpeedX = m_DistancePos.x / 60;

		m_Shot = new FallShot(m_Pos,m_FallSpeedX);
		m_Shot->SetHandle(m_Shothandle);
		m_Shot->SetLookShot(m_LookEnemy);

		m_GraphY = 0;
		m_GraphX = 0;
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
