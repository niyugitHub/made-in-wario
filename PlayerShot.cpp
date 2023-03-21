#include "PlayerShot.h"
#include <DxLib.h>

PlayerShot::PlayerShot(Vec2 Pos, float VecX) : 
	m_handle(-1),
	m_LookLeft(false)
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
		if (!m_LookLeft)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				0,0,64,64,
				m_handle, true,true);
		}

		if (m_LookLeft)
		{
			DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
				0, 0, 64, 64,
				m_handle, true, false);
		}
	}
}
