#include "Shot.h"
#include "game.h"
#include <Dxlib.h>

namespace
{
	// ìäÇ∞ÇΩÇ‡ÇÃÇÃë¨ìx
	constexpr float kFallSpeed = 15.0f;
	// ìäÇ∞ÇΩÇ‡ÇÃÇÃë¨ìxí·â∫
	constexpr float kFallSpeedDown = 0.5f;

	// ìäÇ∞ÇÈïpìx
	constexpr int kFallFrame = 150;
}

Shot::Shot(Vec2 Pos) : 
	m_Pos(Pos),
	m_Vec(0, kFallSpeed)
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

void Shot::Draw(Vec2 offset)
{
	if(m_Exist)
	DrawBox(m_Pos.x + offset.x, m_Pos.y, m_Pos.x + 50 + offset.x, m_Pos.y + 50,
		GetColor(0, 255, 255), true);

//	DrawFormatString(500, 0, GetColor(255, 255, 255), "ìGÇÃêî%f", m_Pos.y);
}
