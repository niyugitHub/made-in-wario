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
	switch (m_ItemNum)
	{
	case 0:
		m_ItemType = kTwoJump;
		m_Pos = { 2000,800 };
		break;
	case 1:
		m_ItemType = kAttackUp;
		m_Pos = { 1300,900 };
		break;
	case 2:
		m_ItemType = kHpUp;
		m_Pos = { 2150,600 };
		break;
	case 3:
		m_ItemType = kAttackUp;
		m_Pos = { 2000,800 };
		break;
	case 4:
		m_ItemType = kAttackUp;
		m_Pos = { 2000,800 };
		break;
	case 5:
		m_ItemType = kAttackUp;
		break;
	case 6:
		m_ItemType = kHpUp;
		break;
	case 7:
		m_ItemType = kAttackUp;
		break;
	case 8:
		m_ItemType = kAttackUp;
		break;
	case 9:
		m_ItemType = kAttackUp;
		break;
	case 10:
		m_ItemType = kAttackUp;
		break;
	case 11:
		m_ItemType = kHpUp;
		break;
	case 12:
		m_ItemType = kAttackUp;
		break;
	case 13:
		m_ItemType = kAttackUp;
		break;
	case 14:
		m_ItemType = kAttackUp;
		break;
	case 15:
		m_ItemType = kAttackUp;
		break;
	}
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
