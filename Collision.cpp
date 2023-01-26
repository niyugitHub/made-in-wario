#include "Collision.h"
#include "Player.h"
#include "Map.h"



Collision::Collision() :
	m_PlayerPos(0, 0),
	m_player(nullptr),
	m_Map(nullptr)
{
}

Collision::~Collision()
{
	
}

void Collision::Update()
{
	m_PlayerPos = m_player->GetPos();
	IsCollision();
}

void Collision::IsCollision()
{
	// プレイヤーの位置
	float PlayerPosX = m_PlayerPos.x / Map::kChipSize;
	float PlayerPosY = m_PlayerPos.y / Map::kChipSize;

	int MapNum[Map::kBgNumY][Map::kBgNumX];
	for (int i = 0; i < Map::kBgNumY; i++)
	{
		for (int j = 0; j < Map::kBgNumX; j++)
		{
			MapNum[i][j] = 0;
		}
	}

	for (int i = PlayerPosY; i < PlayerPosY + 1; i++)
	{
		for (int j = PlayerPosX; j < PlayerPosX + 1; j++)
		{
			MapNum[i][j] = m_Map->GetMapData(i, j);
			////右
			//if (m_PlayerPos.x + Player::kSideSize - 40 < j * Minigame1::kChipSize)
			//{
			//	m_CollRight = true;
			//}
			////左
			//if (m_PlayerPos.x > j * Minigame1::kChipSize + Minigame1::kChipSize / 2)
			//{
			//	m_CollLeft = true;
			//}
			//	
			////下
			//if (m_PlayerPos.y + Player::kColumnSize > i * Minigame1::kChipSize)
			//{
			//	m_CollBottom = true;
			//}
			////上
			//if (m_PlayerPos.y + 10 < i * Minigame1::kChipSize + Minigame1::kChipSize)
			//{
			//	m_CollTop = true;
		}
	}

	for (int i = 0; i < Map::kBgNumY; i++)
	{
		for (int j = 0; j < Map::kBgNumX; j++)
		{
			if (m_Map->GetMapData(i, j) != 0)
			{
				//上
				if (m_PlayerPos.y + 10 < i * Map::kChipSize + Map::kChipSize &&
					m_PlayerPos.y > i * Map::kChipSize + 10 &&
					m_PlayerPos.x + Player::kSideSize - 50 > j * Map::kChipSize &&
					m_PlayerPos.x + 50 < j * Map::kChipSize + Map::kChipSize)
				{
					m_CollTop = true;
				}
				//下
				if (m_PlayerPos.y + (Player::kColumnSize) > i * Map::kChipSize &&
					m_PlayerPos.y + 25 < i * Map::kChipSize/* + Minigame1::kChipSize*/ &&
					m_PlayerPos.x + Player::kSideSize - 45 > j * Map::kChipSize &&
					m_PlayerPos.x + 45 < j * Map::kChipSize + Map::kChipSize)
				{
					m_PlayerPos.y = i * Map::kChipSize - (Player::kColumnSize)+1;
					m_player->SetPos(m_PlayerPos);
					m_CollBottom = true;
				}
				//右
				if (m_PlayerPos.x + Player::kSideSize - 35 > j * Map::kChipSize &&
					m_PlayerPos.x + 60 < j * Map::kChipSize + Map::kChipSize &&
					m_PlayerPos.y + 25 < i * Map::kChipSize + Map::kChipSize &&
					m_PlayerPos.y + (Map::kChipSize * 2) > i * Map::kChipSize + 20)
				{
					m_CollRight = true;
				}
				//左
				if (m_PlayerPos.x + 35 < j * Map::kChipSize + Map::kChipSize &&
					m_PlayerPos.x + Player::kSideSize - 60 > j * Map::kChipSize &&
					m_PlayerPos.y + 25 < i * Map::kChipSize + Map::kChipSize &&
					m_PlayerPos.y + (Map::kChipSize * 2) > i * Map::kChipSize + 20)
				{
					m_CollLeft = true;
				}
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
}

