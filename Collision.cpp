#include "Collision.h"
#include "Player.h"
#include "EnemyFactory.h"
#include "Map.h"
#include "Item.h"
#include<cassert>
#include<DxLib.h>

namespace
{
	// プレイヤーの攻撃の範囲
	constexpr float kAttackRange = 50;
}

Collision::Collision() :
	m_CollTop(false),
	m_CollBottom(false),
	m_CollRight(false),
	m_CollLeft(false),
	m_CollTopEnemy(false),
	m_CollBottomEnemy(false),
	m_CollRightEnemy(false),
	m_CollLeftEnemy(false),
	m_CollEnemy(false),
	m_PlayerPos(0, 0),
	m_EnemyPos(0,0),
	m_ThrowPos(0,0),
	m_MapPos(0,0),
	m_ItemPos(0,0),
	m_CollSingle(false),
	m_MapColl(false),
	m_player(nullptr),
	m_enemy(nullptr),
	m_Map(nullptr),
	m_Item(nullptr)
{
}

Collision::~Collision()
{
	
}

void Collision::Update()
{
	m_PlayerPos = m_player->GetNextPos();

	m_EnemyPos = m_enemy->GetPos();

	/*m_ItemPos = m_Item->GetPos();*/

	if (m_enemy != nullptr)
	{
	}
	else
	{
		m_EnemyPos.x = 0;
		m_EnemyPos.y = 0;
	}

	/*if (m_PlayerPos.y < Game::kScreenHeight)
	{
		IsCollMap();
	}*/

	if (m_enemy != nullptr)
	{
		IsCollMapEnemy();
	}
}

bool Collision::IsCollEnemy()
{
//	if (!m_enemy->isExist()) return false;
	// プレイヤーの位置
	float PlayerPosLeft = m_PlayerPos.x + 30;
	float PlayerPosRight = m_PlayerPos.x + 90;
	float PlayerPosUp = m_PlayerPos.y + 10;
	float PlayerPosBottom = m_PlayerPos.y + 118   ;

	// エネミーの位置
	float EnemyPosLeft = m_EnemyPos.x + m_enemy->GetGraphSize1().x;
	float EnemyPosRight = m_EnemyPos.x + m_enemy->GetGraphSize2().x;
	float EnemyPosUp = m_EnemyPos.y + m_enemy->GetGraphSize1().y;
	float EnemyPosBottom = m_EnemyPos.y + m_enemy->GetGraphSize2().y;

	if (PlayerPosLeft > EnemyPosRight) return false;
	if (PlayerPosRight < EnemyPosLeft) return false;
	if (PlayerPosUp > EnemyPosBottom)  return false;
	if (PlayerPosBottom <  EnemyPosUp)  return false;

	return true;
}

//bool Collision::IsCollThrowEnemy()
//{
//	// プレイヤーの位置
//	float PlayerPosLeft = m_PlayerPos.x + 30;
//	float PlayerPosRight = m_PlayerPos.x + 90;
//	float PlayerPosUp = m_PlayerPos.y + 10;
//	float PlayerPosBottom = m_PlayerPos.y + 118;
//
//	m_ThrowPos = m_enemy->GetThrowPos();
//
//	// エネミーの位置
//	float EnemyPosLeft = m_ThrowPos.x;
//	float EnemyPosRight = m_ThrowPos.x + 50;
//	float EnemyPosUp = m_ThrowPos.y;
//	float EnemyPosBottom = m_ThrowPos.y + 50;
//
//	if (PlayerPosLeft > EnemyPosRight) return false;
//	if (PlayerPosRight < EnemyPosLeft) return false;
//	if (PlayerPosUp > EnemyPosBottom)  return false;
//	if (PlayerPosBottom < EnemyPosUp)  return false;
//
//	return true;
//}

bool Collision::IsCollAttackPlayer()
{
	if (!m_player->GetAttack())
	{
		return false;
	}
	// プレイヤーの位置
	float PlayerPosLeft = m_PlayerPos.x + 30;
	float PlayerPosRight = m_PlayerPos.x + 90;
	float PlayerPosUp = m_PlayerPos.y + 10;
	float PlayerPosBottom = m_PlayerPos.y + 118;

	// エネミーの位置
	float EnemyPosLeft = m_EnemyPos.x + m_enemy->GetGraphSize1().x;
	float EnemyPosRight = m_EnemyPos.x + m_enemy->GetGraphSize2().x;
	float EnemyPosUp = m_EnemyPos.y + m_enemy->GetGraphSize1().y;
	float EnemyPosBottom = m_EnemyPos.y + m_enemy->GetGraphSize2().y;

	if (m_player->GetLook())
	{
		if (PlayerPosLeft - kAttackRange > EnemyPosRight) return false;
		if (PlayerPosRight < EnemyPosLeft) return false;
		if (PlayerPosUp > EnemyPosBottom)  return false;
		if (PlayerPosBottom < EnemyPosUp)  return false;
	}

	if (!m_player->GetLook())
	{
		if (PlayerPosLeft > EnemyPosRight) return false;
		if (PlayerPosRight + kAttackRange < EnemyPosLeft) return false;
		if (PlayerPosUp > EnemyPosBottom)  return false;
		if (PlayerPosBottom < EnemyPosUp)  return false;
	}
	return true;
}

bool Collision::IsCollItem()
{
	m_ItemPos = m_Item->GetPos();
	// プレイヤーの位置
	float PlayerPosLeft = m_PlayerPos.x + 30;
	float PlayerPosRight = m_PlayerPos.x + 90;
	float PlayerPosUp = m_PlayerPos.y + 10;
	float PlayerPosBottom = m_PlayerPos.y + 118;

	// エネミーの位置
	float ItemPosLeft = m_ItemPos.x;
	float ItemPosRight = m_ItemPos.x + 50;
	float ItemPosUp = m_ItemPos.y;
	float ItemPosBottom = m_ItemPos.y + 50;

	if (PlayerPosLeft > ItemPosRight) return false;
	if (PlayerPosRight < ItemPosLeft) return false;
	if (PlayerPosUp > ItemPosBottom)  return false;
	if (PlayerPosBottom < ItemPosUp)  return false;

	return true;
}

//void Collision::IsCollMap()
//{
//	m_PlayerPos = m_player->GetNextPos();
//
//	float PlayerPosX = m_PlayerPos.x / Map::kChipSize;
//	float PlayerPosY = m_PlayerPos.y / Map::kChipSize;
//
//	int MapChipNumX = Map::kBgNumX[m_Map->GetStageNum()];
//	int MapChipNumY = Map::kBgNumY[m_Map->GetStageNum()];
//
//	int MapNum[MapChipNumY][MapChipNumX];
//	for (int i = 0; i < Map::kBgNumY; i++)
//	{
//		for (int j = 0; j < Map::kBgNumX; j++)
//		{
//			MapNum[i][j] = 0;
//		}
//	}
//
//	for (int i = static_cast<int> (PlayerPosY); i < PlayerPosY + 1; i++)
//	{
//		for (int j = static_cast<int>(PlayerPosX); j < PlayerPosX + 1; j++)
//		{
//			MapNum[i][j] = m_Map->GetMapData(i, j);
//		}
//	}
//
//	for (int i = 0; i < Map::kBgNumY; i++)
//	{
//		for (int j = 0; j < Map::kBgNumX; j++)
//		{
//			MapInfo(i, j);
//			if (m_Map->GetMapData(i, j) != 0 && !m_MapColl)
//			{
//				float MapPosX = j * Map::kChipSize;
//				float MapPosY = i * Map::kChipSize;
//
//				if (m_CollSingle && m_PlayerPos.y + 10 < MapPosY + Map::kChipSize - 40 &&
//					m_PlayerPos.y > MapPosY &&
//					m_PlayerPos.x + Player::kSideSize - 50 > MapPosX &&
//					m_PlayerPos.x + 50 < MapPosX + Map::kChipSize)
//				{
//					m_CollTop = true;
//				}
//				//上
//				if (m_PlayerPos.y + 10 < MapPosY + Map::kChipSize &&
//					m_PlayerPos.y > MapPosY &&
//					m_PlayerPos.x + Player::kSideSize - 50 > MapPosX &&
//					m_PlayerPos.x + 50 < MapPosX + Map::kChipSize && !m_CollSingle)
//				{
//					m_CollTop = true;
//				}
//				//右
//				if (m_PlayerPos.x + Player::kSideSize - 35 > MapPosX &&
//					m_PlayerPos.x + 60 < MapPosX + Map::kChipSize &&
//					m_PlayerPos.y + 25 < MapPosY + Map::kChipSize &&
//					m_PlayerPos.y + (Map::kChipSize * 2) > MapPosY + 20 && !m_CollSingle)
//				{
//					m_PlayerPos = m_player->GetPos();
//					m_CollRight = true;
//					m_player->SetPos(m_PlayerPos);
//				}
//				//左
//				if (m_PlayerPos.x + 35 < MapPosX + Map::kChipSize &&
//					m_PlayerPos.x + Player::kSideSize - 60 > MapPosX &&
//					m_PlayerPos.y + 25 < MapPosY + Map::kChipSize &&
//					m_PlayerPos.y + (Map::kChipSize * 2) > MapPosY + 20 && !m_CollSingle)
//				{
//					m_PlayerPos = m_player->GetPos();
//					m_CollLeft = true;
//					m_player->SetPos(m_PlayerPos);
//				}
//				//下
//				if (m_PlayerPos.y + (Player::kColumnSize) > MapPosY &&
//					m_PlayerPos.y + 25 < MapPosY/* + Minigame1::kChipSize*/ &&
//					m_PlayerPos.x + Player::kSideSize - 50 > MapPosX &&
//					m_PlayerPos.x + 50 < MapPosX + Map::kChipSize)
//				{
//					m_PlayerPos.y = MapPosY - (Player::kColumnSize) + 1;
//					m_CollBottom = true;
//					m_player->SetPos(m_PlayerPos);
//				}
//			}
//		}
//	}
//}

//void Collision::IsCollMapEnemy()
//{
//	int EnemyPosX = m_EnemyPos.x / Map::kChipSize;
//	int EnemyPosY = m_EnemyPos.y / Map::kChipSize;
//
//	int MapNum[Map::kBgNumY][Map::kBgNumX];
//	for (int i = 0; i < Map::kBgNumY; i++)
//	{
//		for (int j = 0; j < Map::kBgNumX; j++)
//		{
//			MapNum[i][j] = 0;
//		}
//	}
//
//	for (int i = static_cast<int>(EnemyPosY); i < EnemyPosY; i++)
//	{
//		for (int j = static_cast<int>(EnemyPosX); j < EnemyPosX; j++)
//		{
//			MapNum[i][j] = m_Map->GetMapData(i, j);
//		}
//	}
//
//	for (int i = 0; i < Map::kBgNumY; i++)
//	{
//		for (int j = 0; j < Map::kBgNumX; j++)
//		{
//			if (m_Map->GetMapData(i, j) > 0 && m_Map->GetMapData(i, j) <= Map::kSideMapChipNum * 2)
//			{
//				float MapPosX = j * Map::kChipSize;
//				float MapPosY = i * Map::kChipSize;
//
//				//上
//				if (m_EnemyPos.y + 10 < MapPosY + Map::kChipSize &&
//					m_EnemyPos.y > MapPosY &&
//					m_EnemyPos.x + Player::kSideSize - 50 > MapPosX &&
//					m_EnemyPos.x + 50 < MapPosX + Map::kChipSize)
//				{
//					m_CollTopEnemy = true;
//				}
//				//右
//				if (m_EnemyPos.x + 50 > MapPosX &&
//					m_EnemyPos.x < MapPosX &&
//					m_EnemyPos.y + 25 < MapPosY + Map::kChipSize &&
//					m_EnemyPos.y + 50 >= MapPosY + 20)
//				{
//					m_EnemyPos.x = MapPosX - 50 - 1;
//					m_CollRightEnemy = true;
//					m_enemy->SetPos(m_EnemyPos);
//					
//				}
//				//左
//				if (m_EnemyPos.x < MapPosX + Map::kChipSize &&
//					m_EnemyPos.x > MapPosX &&
//					m_EnemyPos.y + 25 < MapPosY + Map::kChipSize &&
//					m_EnemyPos.y + 50 >= MapPosY + 20)
//				{
//					m_EnemyPos.x = MapPosX + Map::kChipSize + 1;
//					m_CollLeftEnemy = true;
//					m_enemy->SetPos(m_EnemyPos);
//				}
//				//下
//				if (m_EnemyPos.y + 50 >= MapPosY &&
//					m_EnemyPos.y < MapPosY + 50/* + Minigame1::kChipSize*/ &&
//					m_EnemyPos.x + 50 > MapPosX &&
//					m_EnemyPos.x < MapPosX + Map::kChipSize/* &&
//					!m_CollRightEnemy && !m_CollLeftEnemy*/)
//				{
//					m_EnemyPos.y = MapPosY - 50;
//					m_CollBottomEnemy = true;
//					m_enemy->SetPos(m_EnemyPos);
//				}
//
//				////上
//				//if (m_EnemyPos.y + 10 < MapPosY + Map::kChipSize &&
//				//	m_EnemyPos.y > MapPosY &&
//				//	m_EnemyPos.x + Player::kSideSize - 50 > MapPosX &&
//				//	m_EnemyPos.x + 50 < MapPosX + Map::kChipSize)
//				//{
//				//	m_CollTopEnemy = true;
//				//}
//				////下
//				//if (m_EnemyPos.y + 50 > MapPosY &&
//				//	m_EnemyPos.y < MapPosY + 50/* + Minigame1::kChipSize*/ &&
//				//	m_EnemyPos.x + 50 > MapPosX &&
//				//	m_EnemyPos.x < MapPosX + Map::kChipSize)
//				//{
//				//	m_EnemyPos.y = MapPosY - 50;
//				//	m_CollBottomEnemy = true;
//				//	m_enemy->SetPos(m_EnemyPos);
//				//}
//				////右
//				//if (m_EnemyPos.x + 50 > MapPosX &&
//				//	m_EnemyPos.x < MapPosX + Map::kChipSize &&
//				//	m_EnemyPos.y + 25 < MapPosY + Map::kChipSize &&
//				//	m_EnemyPos.y + 50 > MapPosY + 20)
//				//{
//				//	m_CollRightEnemy = true;
//				//}
//				////左
//				//if (m_EnemyPos.x < MapPosX + Map::kChipSize &&
//				//	m_EnemyPos.x + 50 > MapPosX &&
//				//	m_EnemyPos.y + 25 < MapPosY + Map::kChipSize &&
//				//	m_EnemyPos.y + 50 > MapPosY + 20)
//				//{
//				//	m_CollLeftEnemy = true;
//				//}
//			}
//		}
//	}
//}

void Collision::IsCollMapEnemy()
{
	// エネミーの位置
	float EnemyPosLeft = m_EnemyPos.x + m_enemy->GetGraphSize1().x;
	float EnemyPosRight = m_EnemyPos.x + m_enemy->GetGraphSize2().x;
	float EnemyPosUp = m_EnemyPos.y + m_enemy->GetGraphSize1().y;
	float EnemyPosBottom = m_EnemyPos.y + m_enemy->GetGraphSize2().y;

	Vec2 EnemyPosCentor = m_enemy->GetCentorPos();

	for (int i = 0; i < Map::kBgNumY[m_Map->GetStageNum()]; i++)
	{
		for (int j = 0; j < Map::kBgNumX[m_Map->GetStageNum()]; j++)
		{
			if (m_Map->GetMapData(i, j) > 0 && m_Map->GetMapData(i, j) <= Map::kSideMapChipNum * 2)
			{
				float MapTop = i * Map::kChipSize;
				float MapBottom = i * Map::kChipSize + Map::kChipSize;
				float MapRight = j * Map::kChipSize + Map::kChipSize;
				float MapLeft = j * Map::kChipSize;

				//下
				if (EnemyPosBottom >= MapTop &&
					EnemyPosUp < MapTop &&
					EnemyPosRight > MapLeft + 10 &&
					EnemyPosLeft < MapRight - 10)
				{
					m_EnemyPos.y = MapTop - m_enemy->GetGraphSize2().y + 5;
					m_CollBottomEnemy = true;
					m_enemy->SetPos(m_EnemyPos);
				}
				//上
				if (EnemyPosUp < MapBottom &&
					EnemyPosRight > MapLeft + 10 &&
					EnemyPosLeft < MapRight - 10 &&
					EnemyPosBottom > MapTop + 20)
				{
					m_CollTopEnemy = true;
				}
				//右
				if (EnemyPosRight > MapLeft &&
					EnemyPosLeft < MapRight &&
					EnemyPosUp < MapBottom - 20 &&
					EnemyPosBottom >= MapTop + 30 &&
					EnemyPosCentor.x < MapLeft)
				{
					m_CollRightEnemy = true;
				}
				//左
				if (EnemyPosRight > MapLeft &&
					EnemyPosLeft < MapRight &&
					EnemyPosUp < MapBottom - 20 &&
					EnemyPosBottom >= MapTop + 30 &&
					EnemyPosCentor.x > MapRight)
				{
					m_CollLeftEnemy = true;
				}

				////上
				//if (m_EnemyPos.y + 10 < MapPosY + Map::kChipSize &&
				//	m_EnemyPos.y > MapPosY &&
				//	m_EnemyPos.x + Player::kSideSize - 50 > MapPosX &&
				//	m_EnemyPos.x + 50 < MapPosX + Map::kChipSize)
				//{
				//	m_CollTopEnemy = true;
				//}
				////下
				//if (m_EnemyPos.y + 50 > MapPosY &&
				//	m_EnemyPos.y < MapPosY + 50/* + Minigame1::kChipSize*/ &&
				//	m_EnemyPos.x + 50 > MapPosX &&
				//	m_EnemyPos.x < MapPosX + Map::kChipSize)
				//{
				//	m_EnemyPos.y = MapPosY - 50;
				//	m_CollBottomEnemy = true;
				//	m_enemy->SetPos(m_EnemyPos);
				//}
				////右
				//if (m_EnemyPos.x + 50 > MapPosX &&
				//	m_EnemyPos.x < MapPosX + Map::kChipSize &&
				//	m_EnemyPos.y + 25 < MapPosY + Map::kChipSize &&
				//	m_EnemyPos.y + 50 > MapPosY + 20)
				//{
				//	m_CollRightEnemy = true;
				//}
				////左
				//if (m_EnemyPos.x < MapPosX + Map::kChipSize &&
				//	m_EnemyPos.x + 50 > MapPosX &&
				//	m_EnemyPos.y + 25 < MapPosY + Map::kChipSize &&
				//	m_EnemyPos.y + 50 > MapPosY + 20)
				//{
				//	m_CollLeftEnemy = true;
				//}
			}
		}
	}
}

void Collision::InitColl()
{
	m_CollTop = false;
	m_CollBottom = false;
	m_CollRight = false;
	m_CollLeft = false;

	m_CollTopEnemy = false;
	m_CollBottomEnemy = false;
	m_CollRightEnemy = false;
	m_CollLeftEnemy = false;
}

void Collision::PlayerDirectPos()
{
	float PlayerTop = m_PlayerPos.y + 10;
	float PlayerBottom = m_PlayerPos.y + Player::kColumnSize;
	float PlayerRight = m_PlayerPos.x + Player::kSideSize;
	float PlayerLeft = m_PlayerPos.x;
}

void Collision::EnemyDirectPos()
{
	float EnemyTop = m_EnemyPos.y + 10;
	float EnemyBottom = m_EnemyPos.y + 50;
	float EnemyRight = m_EnemyPos.x + 50;
	float EnemyLeft = m_EnemyPos.x;
}

void Collision::MapInfo(int i, int j)
{
	if (m_Map->GetMapData(i, j) == 85 ||
		m_Map->GetMapData(i, j) == 131 ||
		m_Map->GetMapData(i, j) == 132 ||
		m_Map->GetMapData(i, j) == 133)
	{
		m_CollSingle = true;
	}
	else
	{
		m_CollSingle = false;
	}

	if (m_Map->GetMapData(i, j) == 134)
	{
		m_MapColl = true;
	}

	else
	{
		m_MapColl = false;
	}
}

