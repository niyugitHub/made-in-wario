#include "Enemy3.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include "FallShot.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	// 投げたものの速度
	constexpr float kFallSpeed = 15.0f;
	// 投げたものの速度低下
	constexpr float kFallSpeedDown = 0.5f;

	// 投げる頻度
	constexpr int kFallFrame = 120;

	// 画像のサイズ
	constexpr float kGraphSizeX = 125.0f;
	constexpr float kGraphSizeY = 100.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphX = 125;
	constexpr int kRectGraphY = 422;
}

Enemy3::Enemy3() :
	m_GraphFrame(0),
	m_FallSpeedX(0),
	m_FallSpeedY(0),
	m_RandThrowFrame(100)
{
	m_Hp = 60;
	m_GraphX = 0;
	m_GraphY = 0;
	m_Weight = 10.0f;
	m_GraphSize1 = { 0,0 };
	m_GraphSize2 = { kGraphSizeX,kGraphSizeY };
	m_func = &Enemy3::NotUpdate;
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

	if (!m_CollLeft && !m_CollRight)
	{
		m_Pos.x = m_NextPos.x;
	}

	m_Pos.y = m_NextPos.y;

	m_NextPos = m_Pos;


	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2), m_Pos.y + (kGraphSizeY / 2) };

	m_GraphFrame++;

	for (auto& Shot : m_Shot)
	{
		if (Shot != nullptr)
		{
			Shot->Update(m_PlayerPos);
		}
	}

//	std::vector<ShotBase*>::iterator it = m_Shot.begin();

	auto rmIt = std::remove_if(// 条件に合致したものを消す
		m_Shot.begin(), // 対象はm_Shotの最初から
		m_Shot.end(),// 最後まで

		// 消えてもらう条件を表すラムダ式
		// trueだと消える。falseだと消えない。
		[](const std::shared_ptr<ShotBase>& shot) {
			return !shot->GetExist();
		});

	m_Shot.erase(rmIt, m_Shot.end());

	/*for (auto& Shot : m_Shot)
	{

		if (!Shot->GetExist())
		{
			delete Shot;
			Shot = nullptr;

			it = m_Shot.erase(it);
			continue;
		}
		it++;
	}*/

	if (m_Exist)
	{
		BasicMoveEnemy();

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

		m_DistancePos = m_CentorPos - m_PlayerPos;

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

	}

	m_PlayerPos = m_Player->GetPos();

	m_NextPos += m_Vec;
}

void Enemy3::draw(Vec2 offset)
{
	if (m_Exist)
	{
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
	}

	/*DrawBox(m_ThrowPos.x, m_ThrowPos.y, m_ThrowPos.x + 50, m_ThrowPos.y + 50,
		GetColor(0, 255, 255), true);*/
	for (auto& Shot : m_Shot)
	{
		if (Shot != nullptr)
		{
			Shot->Draw(offset);
		}
	}

	m_offset = offset;
//	DrawFormatString(800, 0, GetColor(255, 255, 255), "敵の座標%f", m_Pos.x);
}

void Enemy3::NotUpdate()
{
	if (StartUpdate())
	{
		m_func = &Enemy3::UpdatePatrol;
	}
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

	if (m_DistancePos.x > -500 && m_DistancePos.x < 500 && 
		m_DistancePos.y > -150 && m_DistancePos.y < 400)
	{
		m_func = &Enemy3::UpdateDiscovery;
		m_GraphX = 0;
	}
}

void Enemy3::UpdateDiscovery()
{
	if (m_DistancePos.x < -600 || m_DistancePos.x > 600 ||
		m_DistancePos.y < -150 || m_DistancePos.y > 400)
	{
		m_func = &Enemy3::UpdatePatrol;
		m_GraphY = 0;
		m_GraphX = 0;
		m_RandThrowFrame = 100;
	}

	if (m_RandThrowFrame > 70)
	{
		m_GraphY = 0;
	}

	if (m_RandThrowFrame == 70)
	{
		m_GraphY = 1;
		m_GraphX = 0;
		m_GraphFrame = 1;
	}

	if (m_GraphFrame % 7 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 14 && m_GraphY == 1)
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
		// 投げる頻度ランダム
		int RandFrame = GetRand(80);

		m_RandThrowFrame = kFallFrame + RandFrame;

		m_FallSpeedX = m_DistancePos.x / 60;

//		std::vector<ShotBase*>::iterator it = m_Shot.end();

	
		m_Shot.push_back(std::make_shared<FallShot>(m_CentorPos, m_FallSpeedX));
		m_Shot.back()->SetHandle(m_Shothandle);
		m_Shot.back()->SetLookShot(m_LookEnemy);
		m_Shot.back()->SetExist(true);
		
	//	m_Shot.push_back(Shot);

		m_func = &Enemy3::UpdatePatrol;
		m_GraphY = 0;
		m_GraphX = 0;

		return;	
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
