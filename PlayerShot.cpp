#include "PlayerShot.h"
#include <DxLib.h>

PlayerShot::PlayerShot() : 
	m_Pos(0,0),
	m_Vec(30,0),
	m_Exist(false)
{
}

PlayerShot::~PlayerShot()
{
}

void PlayerShot::Update()
{
	if (m_Exist)
	{
		if (m_LookLeft)
		{
			m_Pos.x -= m_Vec.x;
			m_Pos.y -= m_Vec.y;
		}
		else if(!m_LookLeft)
		{
			m_Pos += m_Vec;
		}
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
