#include "PlayerShot.h"
#include <DxLib.h>

PlayerShot::PlayerShot(Vec2 Pos, float VecX)
{
	m_Pos = Pos;
	m_Vec = { VecX,0 };
}

PlayerShot::~PlayerShot()
{
}

void PlayerShot::Update()
{
	if (m_Exist)
	{
		m_Pos += m_Vec;
	}
}

void PlayerShot::Draw(Vec2 offset)
{
	if (m_Exist)
	{
		DrawBox(m_Pos.x + offset.x, m_Pos.y,
			m_Pos.x + 50 + offset.x, m_Pos.y + 50, GetColor(255, 255, 255), true);
	}
}
