#include "HomingShot.h"
#include "ShotBase.h"
#include "game.h"
#include <Dxlib.h>

namespace
{
	// ‰æ‘œ‚ÌƒTƒCƒY
	constexpr float kGraphSizeX = 50.0f;
	constexpr float kGraphSizeY = 50.0f;

	// ‰æ‘œ‚Ì’ZŒa•”•ª•\Ž¦
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

void HomingShot::Update()
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

	/*if (m_Pos.y < 0 || m_Pos.y > Game::kScreenHeight ||
		m_Pos.x < 0 || m_Pos.y > Game::kScreenWidth)
	{
		m_Exist = false;
	}*/
}

void HomingShot::Draw(Vec2 offset)
{
	if (m_Exist)
		DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
			m_GraphX * kGraphSizeX, kRectGraphY, kGraphSizeX, kGraphSizeY,
			m_handle, true, true);
}
