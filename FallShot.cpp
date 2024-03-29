#include "FallShot.h"
#include "ShotBase.h"
#include "game.h"
#include <Dxlib.h>

namespace
{
	// 投げたものの速度
	constexpr float kFallSpeed = 15.0f;
	// 投げたものの速度低下
	constexpr float kFallSpeedDown = 0.5f;

	// 投げる頻度
	constexpr int kFallFrame = 150;

	// 画像のサイズ
	constexpr float kGraphSizeX = 50.0f;
	constexpr float kGraphSizeY = 50.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 50;
	constexpr int kRectGraphX = 50;
}

FallShot::FallShot(Vec2 Pos, float VecX)
{
	m_Pos = Pos;
	m_Vec = { VecX,kFallSpeed };
}

FallShot::~FallShot()
{
}

void FallShot::Update(Vec2 PlayerPos)
{
	m_Frame++;
	if (m_Frame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX % 6 == 0)
		{
			m_GraphX = 0;
		}
	}

	m_Pos.x -= m_Vec.x;
	m_Pos.y -= m_Vec.y;

	m_Vec.y -= kFallSpeedDown;

	if (m_Pos.y > PlayerPos.y + Game::kScreenHeight ||
		m_Pos.y < PlayerPos.y - Game::kScreenHeight || 
		m_Pos.x > PlayerPos.x + Game::kScreenWidth || 
		m_Pos.x < PlayerPos.x - Game::kScreenWidth)
	{
		m_Exist = false;
		m_Vec.y = kFallSpeed;
	}
}

void FallShot::Draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_LookShot == 1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, true);
		}

		if (m_LookShot == -1)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, false);
		}
	}

//	DrawFormatString(500, 0, GetColor(255, 255, 255), "敵の数%f", m_Pos.y);
}
