#include "HomingShot.h"
#include "ShotBase.h"
#include "game.h"
#include <Dxlib.h>

HomingShot::HomingShot(Vec2 Pos, Vec2 Vec)
{
	m_Pos = Pos;
	m_Vec = Vec;
}

HomingShot::~HomingShot()
{
}

void HomingShot::Update()
{
	m_Pos += m_Vec;

	if (m_Pos.y < 0 || m_Pos.y > Game::kScreenHeight ||
		m_Pos.x < 0 || m_Pos.y > Game::kScreenWidth)
	{
		m_Exist = false;
	}
}

void HomingShot::Draw(Vec2 offset)
{
	if (m_Exist)
		DrawBox(m_Pos.x + offset.x, m_Pos.y, m_Pos.x + 50 + offset.x, m_Pos.y + 50,
			GetColor(0, 255, 255), true);
}
