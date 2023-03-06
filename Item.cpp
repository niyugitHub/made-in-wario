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
		m_ItemType = kGaugeUp;
		m_Pos = { 3000,700 };
		break;
	case 4:
		m_ItemType = kAttackUp;
		m_Pos = { 900,700 };
		break;
	case 5:
		m_ItemType = kShot;
		m_Pos = { 1500,700 };
		break;
	case 6:
		m_ItemType = kHpUp;
		m_Pos = { 2000,700 };
		break;
	case 7:
		m_ItemType = kAttackUp;
		m_Pos = { 2300,700 };
		break;
	case 8:
		m_ItemType = kGaugeUp;
		m_Pos = { 1400,500 };
		break;
	case 9:
		m_ItemType = kAttackUp;
		m_Pos = { 5000,700 };
		break;
	case 10:
		m_ItemType = kAttackUp;
		m_Pos = { 1300,600 };
		break;
	case 11:
		m_ItemType = kHpUp;
		m_Pos = { 3000,800 };
		break;
	case 12:
		m_ItemType = kAttackUp;
		m_Pos = { 2400,700 };
		break;
	case 13:
		m_ItemType = kGaugeUp;
		m_Pos = { 5000,700 };
		break;
	case 14:
		m_ItemType = kAttackUp;
		m_Pos = { 1300,700 };
		break;
	case 15:
		m_ItemType = kAttackUp;
		m_Pos = { 3700,700 };
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
		DrawBox(m_Pos.x + offset.x, m_Pos.y + offset.y,
			m_Pos.x + 50 + offset.x, m_Pos.y + 50 + offset.y,
			GetColor(255, 255, 255), true);

		if (m_ItemType == ItemType::kTwoJump)
		{
			DrawString(m_Pos.x + offset.x, m_Pos.y + offset.y, "ジャンプ", GetColor(0, 255, 0));
		}

		if (m_ItemType == ItemType::kAttackUp)
		{
			DrawString(m_Pos.x + offset.x, m_Pos.y + offset.y, "攻撃力アップ", GetColor(0, 255, 0));
		}

		if (m_ItemType == ItemType::kHpUp)
		{
			DrawString(m_Pos.x + offset.x, m_Pos.y + offset.y, "体力アップ", GetColor(0, 255, 0));
		}

		if (m_ItemType == ItemType::kGaugeUp)
		{
			DrawString(m_Pos.x + offset.x, m_Pos.y + offset.y, "ゲージアップ", GetColor(0, 255, 0));
		}

		if (m_ItemType == ItemType::kShot)
		{
			DrawString(m_Pos.x + offset.x, m_Pos.y + offset.y, "ショット", GetColor(0, 255, 0));
		}
	}


//	if(m_ItemType == kTwoJump)
}
