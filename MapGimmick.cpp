#include "MapGimmick.h"
#include "Map.h"
#include<Dxlib.h>

namespace
{
	// ギミックが落ちる最高速度
	constexpr float kFallSpeedMax = 20.0f;
	// フレームごとにギミックの落ちるスピード上昇
	constexpr float kFallSpeedUp = 0.4f;
}

MapGimmick::MapGimmick(Vec2 Pos) : 
	m_Pos(Pos),
	m_FallSpeed(0),
	m_Flag(false)
{

}

MapGimmick::~MapGimmick()
{
}

void MapGimmick::Init()
{
}

void MapGimmick::Update(Vec2 PlayerPos)
{
	Vec2 DistancePos = m_Pos - PlayerPos;

	if (DistancePos.x < 32 && DistancePos.x > -32 && DistancePos.y < 0)
	{
		m_Flag = true;
	}

	if (m_Flag)
	{
		m_Pos.y += m_FallSpeed;
		if (m_FallSpeed <= kFallSpeedMax)
		{
			m_FallSpeed += kFallSpeedUp;
		}
	}
}

void MapGimmick::Draw(Vec2 offset, int handle)
{
	DrawRectGraph(m_Pos.x + offset.x, m_Pos.y,
		Map::kChipSize * 10, 0,
		Map::kChipSize, Map::kChipSize, handle, true);
}
