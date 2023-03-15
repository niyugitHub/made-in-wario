#include "MapGimmick2.h"
#include<DxLib.h>

namespace
{
	constexpr int kSwitchFrame = 100;
}

MapGimmick2::MapGimmick2(Vec2 Pos, int handle) :
	m_SwitchFrame(GetRand(100)),
	m_GraphFrame(0),
	m_NextGraph(1)
{
	m_Pos = Pos;
	m_handle = handle;
	m_GraphSize1 = { 16,40 };
	m_GraphSize2 = { 48,320 };
	m_Flag = false;
}

MapGimmick2::~MapGimmick2()
{
}

void MapGimmick2::Init()
{
}

void MapGimmick2::Update(Vec2 PlayerPos)
{
	m_SwitchFrame++;

	if (m_SwitchFrame >= kSwitchFrame)
	{
		m_Flag = !m_Flag;
		m_SwitchFrame = 0;
	}

	if (m_Flag)
	{
		m_GraphFrame++;

		if (m_GraphFrame % 10 == 0)
		{
			if (m_GraphX == 1)
			{
				m_NextGraph = 1;
			}

			if (m_GraphX == 3)
			{
				m_NextGraph = -1;
			}

			m_GraphX += m_NextGraph;
		}
	}

	if (!m_Flag)
	{
		m_GraphX = 0;
	}
}

void MapGimmick2::Draw(Vec2 offset)
{
	DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
		m_GraphX * 64, m_GraphY * 64, 64,320,
		m_handle, true, true);

//	DrawGraph(m_Pos.x + offset.x, m_Pos.y + offset.y, m_handle, true);
}
