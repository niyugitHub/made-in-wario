#include "Shot.h"
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
}

Shot::Shot() : 
	m_Pos(0,0),
	m_Vec(0, kFallSpeed),
	m_Exist(false)
{
}

Shot::~Shot()
{
}

void Shot::Update()
{
	m_Pos.x -= m_Vec.x;
	m_Pos.y -= m_Vec.y;

	m_Vec.y -= kFallSpeedDown;

	m_Pos += m_MapVec;

	if (m_Pos.y > Game::kScreenHeight)
	{
		m_Exist = false;
		m_Vec.y = kFallSpeed;
	}
}

void Shot::Draw()
{
	DrawBox(m_Pos.x, m_Pos.y, m_Pos.x + 50, m_Pos.y + 50,
		GetColor(0, 255, 255), true);

	DrawFormatString(500, 0, GetColor(255, 255, 255), "敵の数%f", m_Pos.y);
}
