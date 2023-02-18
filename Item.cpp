#include "Item.h"
#include "Map.h"
#include<DxLib.h>

Item::Item() :
	m_ItemType(0),
	m_Pos(1000,700),
	m_Exist(true)
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
	/*m_Pos += m_Map->GetVec();*/
}

void Item::Draw(Vec2 offset)
{
	if (m_Exist)
	{
		DrawBox(m_Pos.x + offset.x, m_Pos.y,
			m_Pos.x + 50 + offset.x, m_Pos.y + 50,
			GetColor(255, 255, 255), true);
	}

//	if(m_ItemType == kTwoJump)
}
