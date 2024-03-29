#include "HomingShot.h"
#include "ShotBase.h"
#include "game.h"
#include <Dxlib.h>

namespace
{
	// 画像のサイズ
	constexpr float kGraphSizeX = 50.0f;
	constexpr float kGraphSizeY = 50.0f;

	// 画像の短径部分表示
	constexpr int kRectGraphY = 0;
	constexpr int kRectGraphX = 50;
}

HomingShot::HomingShot(Vec2 Pos, Vec2 Vec)
{
	m_Pos = Pos;
	m_Vec = Vec;

	m_GraphX = 0;
	m_GraphY = 0;
}

HomingShot::~HomingShot()
{
}

void HomingShot::Update(Vec2 PlayerPos)
{
	m_Frame++;
	if (m_Frame % 5 == 0)
	{
		m_GraphX++;

		if (m_GraphX % 4 == 0)
		{
			m_GraphX = 0;
		}
	}

	m_Pos += m_Vec;

	if (m_Pos.y > PlayerPos.y + Game::kScreenHeight ||
		m_Pos.y < PlayerPos.y - Game::kScreenHeight ||
		m_Pos.x > PlayerPos.x + Game::kScreenWidth ||
		m_Pos.x < PlayerPos.x - Game::kScreenWidth)
	{
		m_Exist = false;
	}
}

void HomingShot::Draw(Vec2 offset)
{
	if (m_Exist)
	{
		if (m_ShotSize2.x == 50)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				m_GraphX * kGraphSizeX, kRectGraphY, kGraphSizeX, kGraphSizeY,
				m_handle, true, true);
		}

		else
		{
			DrawRectRotaGraph(m_Pos.x + offset.x + 50, m_Pos.y + offset.y + 50,
				m_GraphX * kGraphSizeX, kRectGraphY, kGraphSizeX, kGraphSizeY,
				2.0f,0.0f,m_handle, true, true);
		}
	}
}
