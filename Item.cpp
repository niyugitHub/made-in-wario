#include "Item.h"
#include "Map.h"
#include<DxLib.h>

Item::Item() :
	m_Pos(1000,700)
{
}

Item::~Item()
{
}

void Item::Init()
{
}

void Item::Update()
{
	m_Pos += m_Map->GetVec();
}

void Item::Draw()
{
	DrawBox(m_Pos.x, m_Pos.y,
		m_Pos.x + 50, m_Pos.y + 50,
		GetColor(255, 255, 255), true);
}
