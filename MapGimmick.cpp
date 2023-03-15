#include "MapGimmick.h"
#include "GimmickBase.h"
#include "Map.h"
#include<Dxlib.h>

namespace
{
	// ギミックが落ちる最高速度
	constexpr float kFallSpeedMax = 20.0f;
	// フレームごとにギミックの落ちるスピード上昇
	constexpr float kFallSpeedUp = 0.4f;
}

MapGimmick::MapGimmick(Vec2 Pos ,int handle) :
	m_FallSpeed(0),
	m_GimmickMove(false)
{
	m_GraphSize1 = { 10,20 };
	m_GraphSize2 = { 55,80 };
	m_Pos = Pos;
	m_handle = handle;
	m_Flag = true;
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

	if (m_offset.x < -Game::kScreenWidth / 2)
	{
		m_offset.x = -Game::kScreenWidth / 2;
	}

	if (m_offset.y < -Game::kScreenHeight / 2)
	{
		m_offset.y = -Game::kScreenHeight / 2;
	}
	/*if (m_DistancePos.x < Game::kScreenWidth + m_offset.x + 200 && m_DistancePos.x > -Game::kScreenWidth + m_offset.x - 200 &&
		m_DistancePos.y < Game::kScreenHeight + m_offset.y + 200 && m_DistancePos.y > -Game::kScreenHeight + m_offset.y - 200)
	{
		return true;
	}
	return false;*/

	if (DistancePos.x < 96 && DistancePos.x > -32 && 
		DistancePos.y < 0 && DistancePos.y > -Game::kScreenHeight - m_offset.y)
	{
		m_GimmickMove = true;
	}

	if (m_GimmickMove)
	{
		m_Pos.y += m_FallSpeed;
		if (m_FallSpeed <= kFallSpeedMax)
		{
			m_FallSpeed += kFallSpeedUp;
		}
	}
}

void MapGimmick::Draw(Vec2 offset)
{
	m_offset = offset;
	DrawGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
		m_handle, true);
}
