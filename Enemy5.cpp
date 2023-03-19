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
	constexpr float kMoveChaseMax= 5.0f;

	// 通常時の速度
	constexpr float kMoveFly = 0.05f;

	// ショットを打つまでのフレーム
	constexpr int kShotFrame = 40;
	constexpr int kNextShotFrame = 180;

	// ショットのスピード
	constexpr float kShotSpeed = 10.0f;

	// 画像のサイズ
	constexpr float kGraphSizeX = 122.0f;
	constexpr float kGraphSizeY = 130.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 192;
	constexpr int kRectGraphX = 122;
}

Enemy5::Enemy5() :
	m_Frame(35),
	m_GraphFrame(0),
	m_ShotFrame(0),
	m_NextShotFrame(kNextShotFrame),
	m_FlySpeed(-kMoveFly),
	m_FieldSpeed(0.0f)
{
	m_Weight = 1.5f;
	m_Hp = 120;
	m_GraphSize2 = { 20,20 };
	m_GraphSize2 = { kGraphSizeX - 20,kGraphSizeY - 20 };
	m_func = &Enemy5::NotUpdate;
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

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos.x = m_NextPos.x;
	}

	if (!m_CollTop)
	{
		m_Pos.y = m_NextPos.y;
	}

	m_NextPos = m_Pos;

	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2), m_Pos.y + (kGraphSizeY / 2) };

	m_GraphFrame++;

	auto rmIt = std::remove_if(// 条件に合致したものを消す
		m_Shot.begin(), // 対象はm_Shotの最初から
		m_Shot.end(),// 最後まで

		// 消えてもらう条件を表すラムダ式
		// trueだと消える。falseだと消えない。
		[](const std::shared_ptr<ShotBase>& shot) {
			return !shot->GetExist();
		});

	m_Shot.erase(rmIt, m_Shot.end());

	//for (auto& Shot : m_Shot)
	//{
	//	if (!Shot->GetExist())
	//	{
	//		/*delete Shot;
	//		Shot = nullptr;*/

	//		m_Shot.erase(it,it);
	//		continue;
	//	}
	//	it++;
	//}

	if (m_DistancePos.x < 0)
	{
		m_LookEnemy = -1;
	}

	else
	{
		m_LookEnemy = 1;
	}

	if (m_Exist)
	{
		m_PlayerPos = m_Player->GetPos();

		m_DistancePos = m_CentorPos - m_PlayerPos;

		(this->*m_func)();
	}

	for (auto& Shot : m_Shot)
	{
		if (Shot != nullptr)
		{
			Shot->Update(m_PlayerPos);
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
		if (m_LookEnemy == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, true);
		}

		if (m_LookEnemy == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, false);
		}
	}

	for (auto& Shot : m_Shot)
	{
		if (Shot != nullptr)
		{
			Shot->Draw(offset);
		}
	}

	m_offset = offset;
}

void Enemy5::NotUpdate()
{
	if (StartUpdate())
	{
		m_func = &Enemy5::UpdatePatrol;
	}
}

void Enemy5::UpdatePatrol()
{
	BasicMoveEnemy();

	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX % 8 == 0)
		{
			m_GraphX = 0;
		}
	}

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

	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 13)
		{
			m_GraphX = 9;
		}
	}

	if(m_ShotFrame <= 0)
	{
		BasicMoveEnemy();

		if (m_DistancePos.x < kPlayerGraphSize / 2)
		{
			if (m_FieldSpeed < kMoveChaseMax)
			{
				m_FieldSpeed += kMoveChaseField;
			}
		}

		if (m_DistancePos.x >= kPlayerGraphSize / 2)
		{
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

		m_Vec.x = m_FieldSpeed;

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

		m_NextPos += m_Vec;
	}
}

void Enemy5::UpdateAttackShot()
{
	m_ShotFrame++;

	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 8)
		{
			m_GraphX = 0;
		}
	}

	if (m_ShotFrame >= kShotFrame)
	{
		m_NextShotFrame = 0;

		Vec2 PlayerPos = { m_PlayerPos.x + (Player::kSideSize / 2) ,m_PlayerPos.y + Player::kColumnSize / 2 };
		Vec2 vel = m_Pos - PlayerPos;

		vel = vel.normalize();
		vel *= -kShotSpeed;

		
		m_Shot.push_back(std::make_shared<HomingShot>(m_Pos, vel));
		m_Shot.back()->SetHandle(m_Shothandle);
		m_Shot.back()->SetLookShot(m_LookEnemy);
		m_Shot.back()->SetExist(true);
		
		m_func = &Enemy5::UpdateDiscovery;

		

	//	return;	
	}
}
