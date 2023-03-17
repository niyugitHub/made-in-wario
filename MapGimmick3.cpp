#include "MapGimmick3.h"
#include<DxLib.h>

namespace
{
	// ‰ñ“]‚Ì‘¬“x
	constexpr float kRotaSpeed = 0.06f;

	// ‰æ‘œ‚ÌƒTƒCƒY
	constexpr float kGraphSizeX = 100;
	constexpr float kGraphSizeY = 100;

	// ‰ñ“]‚Ì”¼Œa
	constexpr float kRotaSize= 200.0f;
}

MapGimmick3::MapGimmick3(Vec2 Pos, int handle) : 
	m_BloakPos(Pos.x - 20,Pos.y - 10),
	m_Rota(0.0f)
{
	m_Pos = { Pos.x + kRotaSize,Pos.y};
	m_handle = handle;
	m_GraphSize1 = { 25,25};
	m_GraphSize2 = { 75,75 };
	m_Flag = true;
}

MapGimmick3::~MapGimmick3()
{
}

void MapGimmick3::Init()
{
}

void MapGimmick3::Update(Vec2 PlayerPos)
{
	m_Pos = { m_BloakPos.x,m_BloakPos.y };

	m_Rota -= kRotaSpeed;

	m_Vec.x = cos(m_Rota) * kRotaSize;
	m_Vec.y = sin(m_Rota) * kRotaSize;

	m_Pos += m_Vec;
}

void MapGimmick3::Draw(Vec2 offset)
{
	DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
		0, 50, 100, 100,
		m_handle, true, true);

	Vec2 DistancePos = m_BloakPos - m_Pos;

	for (int i = 1; i <= 5; i++)
	{
		Vec2 Pos = { 0,0 };
		if (i == 1)
		{
			Pos = DistancePos / 1.2;
		}
		if (i == 2)
		{
			Pos = DistancePos / 1.5;
		}
		if (i == 3)
		{
			Pos = DistancePos / 2;
		}
		if (i == 4)
		{
			Pos = DistancePos / 3;
		}
		if (i == 5)
		{
			Pos = DistancePos / 5;
		}

		Pos += {-32, -32};

		DrawRectGraph(m_BloakPos.x - Pos.x + offset.x, m_BloakPos.y - Pos.y + offset.y,
			0, 0, 50, 50,
			m_handle, true, true);
	}
}
