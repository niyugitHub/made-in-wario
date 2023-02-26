#include "FallShot.h"
#include "ShotBase.h"
#include "game.h"
#include <Dxlib.h>

namespace
{
	// ���������̂̑��x
	constexpr float kFallSpeed = 15.0f;
	// ���������̂̑��x�ቺ
	constexpr float kFallSpeedDown = 0.5f;

	// ������p�x
	constexpr int kFallFrame = 150;
}

FallShot::FallShot(Vec2 Pos, float VecX)
{
	m_Pos = Pos;
	m_Vec = { VecX,kFallSpeed };
}

FallShot::~FallShot()
{
}

void FallShot::Update()
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

void FallShot::Draw(Vec2 offset)
{
	if(m_Exist)
	DrawBox(m_Pos.x + offset.x, m_Pos.y, m_Pos.x + 50 + offset.x, m_Pos.y + 50,
		GetColor(0, 255, 255), true);

//	DrawFormatString(500, 0, GetColor(255, 255, 255), "�G�̐�%f", m_Pos.y);
}
