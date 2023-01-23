#include "Collision.h"
#include "Player.h"
#include "Minigame1.h"

Collision::~Collision()
{
	m_PlayerPos.y = 0;
	m_PlayerPos.x = 0;
	m_Map = new Minigame1;
	m_player = new Player;
}

void Collision::Update()
{
	m_PlayerPos = m_player->GetPos();
}

bool Collision::IsCollTop()
{
	// プレイヤーの位置
	int PlayerPosX = m_PlayerPos.x / Minigame1::kChipSize;
	int PlayerPosY = m_PlayerPos.y / Minigame1::kChipSize;

	int MapNum[Minigame1::kBgNumY][Minigame1::kBgNumX];
	for (int i = 0; i < Minigame1::kBgNumY; i++)
	{
		for (int j = 0; j < Minigame1::kBgNumX; j++)
		{
			MapNum[i][j] = 0;
		}
	}

	for (int i = 0; i < Minigame1::kBgNumY; i++)
	{
		for (int j = 0; j < Minigame1::kBgNumX; j++)
		{
			if (m_Map->GetMapData(i, j) != 0)
			{
				//上
				if (m_PlayerPos.y + 10 < i * Minigame1::kChipSize + Minigame1::kChipSize &&
					m_PlayerPos.y > i * Minigame1::kChipSize &&
					m_PlayerPos.x + Player::kSideSize - 40 > j * Minigame1::kChipSize &&
					m_PlayerPos.x - Player::kSideSize + 40 < j * Minigame1::kChipSize + Minigame1::kChipSize)
				{
					 return true;
				}
				//////下
				////if (m_PlayerPos.y + Player::kColumnSize > i * Minigame1::kChipSize &&
				////	m_PlayerPos.x + Player::kSideSize - 40 > j * Minigame1::kChipSize &&
				////	m_PlayerPos.x < j * Minigame1::kChipSize + Minigame1::kChipSize / 2)
				////{
				////	m_CollBottom = true;
				////}
				////右
				//if (m_PlayerPos.x + Player::kSideSize - 40 > j * Minigame1::kChipSize &&
				//	m_PlayerPos.x < j * Minigame1::kChipSize + Minigame1::kChipSize &&
				//	m_PlayerPos.y + 10 < i * Minigame1::kChipSize + Player::kColumnSize &&
				//	m_PlayerPos.y + +(Minigame1::kChipSize * 2) > i * Minigame1::kChipSize)
				//{
				//	m_CollRight = true;
				//}
				////左
				//if (m_PlayerPos.x > j * Minigame1::kChipSize + Minigame1::kChipSize / 2 &&
				//	m_PlayerPos.y + Player::kColumnSize < i * Minigame1::kChipSize &&
				//	m_PlayerPos.y + 20 > i * Minigame1::kChipSize + Minigame1::kChipSize)
				//{
				//	m_CollLeft = true;
				//}
			}
		}
	}

	return false;
}

bool Collision::IsCollBottom()
{
	return false;
}

bool Collision::IsCollLeft()
{
	return false;
}

bool Collision::IsCollRight()
{
	return false;
}
