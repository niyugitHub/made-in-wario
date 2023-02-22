#include "MapGimmick.h"
#include "Map.h"
#include<Dxlib.h>

namespace
{
	constexpr float m_FallSpeedMax = 20.0f;
}

MapGimmick::MapGimmick(Vec2 Pos) : 
	m_Pos(Pos),
	m_FallSpeed(0),
	Flag(false)
{

}

MapGimmick::~MapGimmick()
{
}

void MapGimmick::Init()
{
}

void MapGimmick::Update()
{
	if (Flag)
	{
		m_Pos.y -= m_FallSpeed;
	}
}

void MapGimmick::Draw(int handle)
{
	DrawRectGraph(m_Pos.x + Map::kChipSize, m_Pos.y + Map::kChipSize,
		Map::kChipSize * 9, 0,
		Map::kChipSize, Map::kChipSize, handle, true);
}
