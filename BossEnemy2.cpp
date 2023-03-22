#include "BossEnemy2.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include "HomingShot.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	constexpr float kPlayerGraphSize = 100.0f;

	// 画像のサイズ
	constexpr float kGraphSizeX = 960.0f;
	constexpr float kGraphSizeY = 330.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 6400;
	constexpr int kRectGraphX = 6300;

	// 移動速度(通常)
	constexpr float kSpeed = 3.0f;

	// 移動速度(ダッシュ時)
	constexpr float kDashSpeed = 7.0f;

	constexpr float kJump = -23.0f;
	constexpr float kJumpDown = 1.0f;

	// ショットのスピード
	constexpr float kShotSpeed = 15.0f;

	// HPバーの長さ
	constexpr int kHpBar = 1320;

	// 最大HP 
	constexpr int kHpMax = 1500;

	// 画像
	const char* const kHpBar1GraphicFilename = "data/HpBar1.png";
	const char* const kHpBar2GraphicFilename = "data/HpBar2.png";
}

BossEnemy2::BossEnemy2() :
	m_Frame(80),
	m_GraphFrame(0),
	m_NowAttack(false),
	m_HpBar(kHpBar),
	m_Jump(0.0f)
{
	m_Hp = kHpMax;
	m_GraphX = 0;
	m_GraphY = 0;
	m_Weight = 100.0f;
	m_GraphSize1 = { 400,100 };
	m_GraphSize2 = { kGraphSizeX - 400,kGraphSizeY - 40 };
	m_func = &BossEnemy2::UpdateNotBattle;

	m_HpBarHandle1 = LoadGraph(kHpBar1GraphicFilename);
	m_HpBarHandle2 = LoadGraph(kHpBar2GraphicFilename);
}

BossEnemy2::~BossEnemy2()
{
}

void BossEnemy2::update()
{
	if (m_Hp <= 0 && m_func != &BossEnemy2::UpdateDead)
	{
		m_Exist = false;
		m_GraphY = 6;
		m_GraphX = 0;
		m_Vec.x = 0;
		m_Vec.y = 0;
		m_GraphFrame = 0;
		m_func = &BossEnemy2::UpdateDead;
	}

	if (!m_CollRight && !m_CollLeft)
	{
		m_Pos.x = m_NextPos.x;
	}

	m_Pos.y = m_NextPos.y;

	m_NextPos = m_Pos;

	m_CentorPos = { m_Pos.x + (kGraphSizeX / 2) - 50 , m_Pos.y + kGraphSizeY - 100 };

	m_GraphFrame++;

	auto rmIt = std::remove_if(// 条件に合致したものを消す
		m_Shot.begin(), // 対象はm_Shotの最初から
		m_Shot.end(),// 最後まで

		// 消えてもらう条件を表すラムダ式
		// falseだと消える。trueだと消えない。
		[](const std::shared_ptr<ShotBase>& shot) {
			return !shot->GetExist();
		});

	m_Shot.erase(rmIt, m_Shot.end());

	if (m_DistancePos.x < 0 && !m_NowAttack)
	{
		m_LookEnemy = -1;
	}

	else if (!m_NowAttack)
	{
		m_LookEnemy = 1;
	}

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

	if (m_Exist)
	{
		m_PlayerPos = m_Player->GetPos();

		m_DistancePos = m_CentorPos - m_PlayerPos;

	}
	(this->*m_func)();

	for (auto& Shot : m_Shot)
	{
		if (Shot != nullptr)
		{
			Shot->Update(m_PlayerPos);
		}
	}

	m_NextPos += m_Vec;
}

void BossEnemy2::draw(Vec2 offset)
{
	if (m_Exist)
	{
		
	}

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

	for (auto& Shot : m_Shot)
	{
		if (Shot != nullptr)
		{
			Shot->Draw(offset);
		}
	}

	float HpPercent = static_cast<float>(m_Hp) / static_cast<float>(kHpMax);

	if (m_BossBattle)
	{
		DrawRectGraph(300, 150,
			0, 0, kHpBar, 50,
			m_HpBarHandle2, true, false);
		/*DrawBox(300, 150, 300 + kHpBar, 200,
			0x000000, true);*/

		DrawRectGraph(300, 150,
			0, 0, m_HpBar * HpPercent, 50,
			m_HpBarHandle1, true, false);
		/*DrawBox(300, 150, 300 + m_HpBar * HpPercent, 200,
			0xff0000, true);*/
	}

	m_offset = offset;
}

void BossEnemy2::ChangeGraph(int i)
{
	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;
		if (m_GraphX >= i)
		{
			m_GraphX = 0;
		}
	}
}

void BossEnemy2::UpdateNotBattle()
{
	if (m_GraphFrame % 5 == 0)
	{
		m_GraphX++;
	}

	if (m_GraphX >= 9)
	{
		if (m_GraphY == 1)
		{
			m_GraphY = 0;
		}

		if (m_GraphY == 0)
		{
			m_GraphY = 1;
		}

		m_GraphX = 0;
	}
	m_Vec.x = 0;

	if (m_DistancePos.x < 800 && m_DistancePos.x > -800 &&
		m_DistancePos.y < 500 && m_DistancePos.y > -500)
	{
		m_BossBattle = true;
	}

	if (m_BossBattle)
	{
		m_func = &BossEnemy2::UpdateDiscovery;
	}
}

void BossEnemy2::UpdateDiscovery()
{
	m_Frame--;
	m_GraphY = 7;

	m_GraphSize1 = { 400,150 };
	m_GraphSize2 = { kGraphSizeX - 400,kGraphSizeY - 40 };

	if (m_DistancePos.x < 0)
	{
		m_Vec.x = kSpeed;
	}

	if (m_DistancePos.x >= 0)
	{
		m_Vec.x = -kSpeed;
	}

	ChangeGraph(6);

	if (m_DistancePos.x < 180 && m_DistancePos.x > -180 && m_Frame <= 0)
	{
		m_Frame = 50 + GetRand(50);
		int RandAttack = GetRand(1);

		if (RandAttack == 0)
		{
			m_func = &BossEnemy2::UpdateAttack1;
			m_GraphFrame = 0;
			m_GraphX = 0;
			m_GraphY = 5;
			m_Vec.x = 0;
			m_NowAttack = true;
		}
		if (RandAttack == 1)
		{
			m_func = &BossEnemy2::UpdateAttack2;
			m_GraphFrame = 0;
			m_GraphX = 0;
			m_GraphY = 3;
			m_Vec.x = 0;
			m_NowAttack = true;
		}
	}

	int RandAttack = GetRand(320);

	if (RandAttack == 1)
	{
		m_Frame = 50 + GetRand(50);
		m_func = &BossEnemy2::UpdateAttack3;
		m_GraphFrame = 0;
		m_GraphX = 0;
		m_Vec.x = 0;
		m_Jump = kJump;
		m_NowAttack = true;
	}

	if (RandAttack == 2 && m_Hp <= 800)
	{
		m_Frame = 50 + GetRand(50);
		m_func = &BossEnemy2::UpdateAttack4;
		m_GraphFrame = 0;
		m_GraphX = 0;
		m_GraphY = 2;
		m_Vec.x = 0;
	}
}

void BossEnemy2::UpdateAttack1()
{
	if (m_GraphFrame >= 40 && m_GraphFrame % 5 == 0)
	{
		if (m_GraphX <= 2 || m_GraphX >= 7)
		{
			if (m_LookEnemy == -1 && m_GraphFrame <= 50)
			{
				m_GraphSize1 = { 400,150 };
				m_GraphSize2 = { kGraphSizeX - 250,kGraphSizeY - 40 };
			}

			else if (m_LookEnemy == 1 && m_GraphFrame <= 50)
			{
				m_GraphSize1 = { 250,150 };
				m_GraphSize2 = { kGraphSizeX - 400,kGraphSizeY - 40 };
			}

			else
			{
				m_GraphSize1 = { 400,150 };
				m_GraphSize2 = { kGraphSizeX - 400,kGraphSizeY - 40 };
			}
		}

		m_GraphX++;
		if (m_GraphX >= 10)
		{
			m_GraphX = 0;
		}
	}

	if (m_GraphFrame >= 90)
	{
		m_func = &BossEnemy2::UpdateDiscovery;
		m_NowAttack = false;
	}
}

void BossEnemy2::UpdateAttack2()
{
	if (m_GraphFrame >= 50 && m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 6)
		{
			m_GraphX = 0;
		}

		if (m_LookEnemy == -1)
		{
			m_Vec.x = kSpeed * 4.0f;
			m_GraphSize1 = { 400,220 };
			m_GraphSize2 = { kGraphSizeX - 350,kGraphSizeY - 40 };
		}

		if (m_LookEnemy == 1)
		{
			m_Vec.x = -kSpeed * 4.0f;
			m_GraphSize1 = { 350,220 };
			m_GraphSize2 = { kGraphSizeX - 400,kGraphSizeY - 40 };
		}
	}


	if (m_GraphFrame >= 150)
	{
		m_func = &BossEnemy2::UpdateDiscovery;
		m_NowAttack = false;
	}

	if (m_CollLeft || m_CollRight)
	{
		m_func = &BossEnemy2::UpdateDiscovery;
		m_NowAttack = false;
	}
}

void BossEnemy2::UpdateAttack3()
{
	if (m_GraphFrame >= 60)
	{
		m_GraphY = 4;
		if (m_Jump < 20)
		{
			m_GraphX = 3;
		}

		if (m_Jump < 10)
		{
			m_GraphX = 2;
		}

		if (m_Jump < 0)
		{
			m_GraphX = 1;
		}

		if (m_GraphX >= 8)
		{
			m_GraphX = 0;
		}

		if (m_LookEnemy == -1)
		{
			m_Vec.x = kSpeed * 3.5f;
		}

		if (m_LookEnemy == 1)
		{
			m_Vec.x = -kSpeed * 3.5f;
		}

		m_Vec.y = m_Jump;

		m_Jump += kJumpDown;
	}

	if (m_CollBottom && m_GraphFrame >= 100)
	{
		m_func = &BossEnemy2::UpdateDiscovery;
		m_NowAttack = false;
		m_Jump = 0;
	}
}

void BossEnemy2::UpdateAttack4()
{
	if (m_GraphFrame >= 50 && m_GraphFrame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX >= 6)
		{
			m_GraphX = 0;
		}

		if (m_GraphX == 3 && m_GraphFrame % 5 == 0)
		{
			Vec2 Pos = { 0,0 };
			if (m_LookEnemy == 1)
			{
				Pos = { m_Pos.x + 400,m_Pos.y + 100 };
			}

			if (m_LookEnemy == -1)
			{
				Pos = { m_Pos.x + (kGraphSizeX - 400),m_Pos.y + 100};
			}

			Vec2 PlayerPos = { m_PlayerPos.x + (Player::kSideSize / 2) ,m_PlayerPos.y + Player::kColumnSize / 2 };
			Vec2 vel = Pos - PlayerPos;

			vel = vel.normalize();
			vel *= -kShotSpeed;


			m_Shot.push_back(std::make_shared<HomingShot>(Pos, vel));
			m_Shot.back()->SetHandle(m_Shothandle);
			m_Shot.back()->SetLookShot(m_LookEnemy);
			m_Shot.back()->SetShotSize1({10,10});
			m_Shot.back()->SetShotSize2({ 90,90 });
			m_Shot.back()->SetExist(true);
		}
	}

	if (m_GraphFrame >= 150)
	{
		m_func = &BossEnemy2::UpdateDiscovery;
		m_NowAttack = false;
	}
}

void BossEnemy2::UpdateDead()
{
	if (m_GraphFrame % 8 == 0)
	{
		m_GraphX++;
		if (m_GraphX >= 5)
		{
			m_GraphX = 5;
		}
		if (m_GraphFrame >= 100)
		{
			//	m_BossBattle = false;
			m_GameClear = true;
		}
	}
}
