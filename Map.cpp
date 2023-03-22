#include<Dxlib.h>

#include "Map.h"
#include "MapGimmick.h"
#include "MapGimmick2.h"
#include "MapGimmick3.h"
#include "GimmickBase.h"
#include "game.h"
#include "Pad.h"
#include <cassert>

namespace
{
	// 入出力ファイル名
	const char* const kFileName = "data/Assets(64×64).png";
	const char* const kFileGimmickName = "data/gimmick.png";
	const char* const kFileGimmick2Name = "data/Fire.png";
	const char* const kFileGimmick3Name = "data/Gimmick3.png";

	const char* const kFileBackGroundName[5] =
	{
		"data/background1.png",
		"data/background2.png",
		"data/background3.png",
		"data/background4.png",
		"data/background5.png",
	};

	// チップの数
	static constexpr int kBgNumY[5] = {20,60,17,17,17};
	static constexpr int kBgNumX[5] = { 150,100,150,150,150 };
}

Map::Map() :
	m_CollLeft(false),
	m_CollRight(false),
	m_PlayerPos(0,0),
	m_BackGroundPos(0,0),
	m_handle(-1),
	m_StageNum(4),
	m_graphWidth(0),
	m_graphHeight(0),
	m_LeftNum(0),
	m_RightNum(0),
	m_Pos(0, 0),
	m_ScrollSpeed(0, 0),
	m_Vec(0,0),
	m_GimmickCount(0)
{
	for (int i = 0; i < kBgNumY[m_StageNum]; i++)
	{
		for (int j = 0; j < kBgNumX[m_StageNum]; j++)
		{
			m_MapData[i][j] = kMapData1[i][j];
		}
	}

	/*for (auto& GimmickPos : m_GimmickPos)
	{
		GimmickPos = { 0,0 };
	}*/
}

Map::~Map()
{
}

bool Map::GetGimmickFlag(int i)
{
	return m_Gimmick[i]->GetFlag();
}

Vec2 Map::GetGimmickPos(int i)
{
	return m_Gimmick[i]->GetPos();
}

Vec2 Map::GetGimmickSize1(int i)
{
	return m_Gimmick[i]->GetGraphSize1();
}

Vec2 Map::GetGimmickSize2(int i)
{
	return m_Gimmick[i]->GetGraphSize2();
}

void Map::Init()
{
	for (int y = 0; y < 500; y++)
	{
		for (int x = 0; x < 500; x++)
		{
			m_MapData[y][x] = 0;
		}
	}

	m_Gimmick.erase(m_Gimmick.begin(), m_Gimmick.end());

	switch (m_StageNum)
	{
	case 0:
		for (int y = 0; y < kBgNumY[m_StageNum]; y++)
		{
			for (int x = 0; x < kBgNumX[m_StageNum]; x++)
			{
				m_MapData[y][x] = kMapData1[y][x];
			}
		}
		break;

	case 1:
		for (int y = 0; y < kBgNumY[m_StageNum]; y++)
		{
			for (int x = 0; x < kBgNumX[m_StageNum]; x++)
			{
				m_MapData[y][x] = kMapData2[y][x];
			}
		}
		break;

	case 2:
		for (int y = 0; y < kBgNumY[m_StageNum]; y++)
		{
			for (int x = 0; x < kBgNumX[m_StageNum]; x++)
			{
				m_MapData[y][x] = kMapData3[y][x];
			}
		}
		break;

	case 3:
		for (int y = 0; y < kBgNumY[m_StageNum]; y++)
		{
			for (int x = 0; x < kBgNumX[m_StageNum]; x++)
			{
				m_MapData[y][x] = kMapData4[y][x];
			}
		}
		break;

	case 4:
		for (int y = 0; y < kBgNumY[m_StageNum]; y++)
		{
			for (int x = 0; x < kBgNumX[m_StageNum]; x++)
			{
				m_MapData[y][x] = kMapData5[y][x];
			}
		}
		break;
	}

	for (int y = 0; y < kBgNumY[m_StageNum]; y++)
	{
		for (int x = 0; x < kBgNumX[m_StageNum]; x++)
		{
			if (m_MapData[y][x] == 255)
			{
				Vec2 GimmickPos = { kChipSize * x, kChipSize * y };
				m_Gimmick.push_back(std::make_shared<MapGimmick>(GimmickPos, m_GimmickHandle));
			}

			if (m_MapData[y][x] == 15)
			{
				Vec2 GimmickPos = { kChipSize * x, kChipSize * y - (kChipSize * 4)};
				m_Gimmick.push_back(std::make_shared<MapGimmick2>(GimmickPos, m_GimmickHandle2));
			}

			if (m_MapData[y][x] == 16 || m_MapData[y][x] == 17)
			{
				Vec2 GimmickPos = { kChipSize * x, kChipSize * y };
				m_Gimmick.push_back(std::make_shared<MapGimmick3>(GimmickPos, m_GimmickHandle3));
			}
		}
	}
}

void Map::load()
{
	m_handle = LoadGraph(kFileName);
	GetGraphSize(m_handle, &m_graphWidth, &m_graphHeight);

	m_GimmickHandle = LoadGraph(kFileGimmickName);
	m_GimmickHandle2 = LoadGraph(kFileGimmick2Name);
	m_GimmickHandle3 = LoadGraph(kFileGimmick3Name);

	for (int i = 0; i < 5; i++)
	{
		m_BackGroundHandle[i] = LoadGraph(kFileBackGroundName[i]);
	}
}

void Map::unload()
{
	DeleteGraph(m_handle);
}

void Map::update()
{
	m_GimmickCount = 0;
	for (auto& Gimmick : m_Gimmick)
	{
		Gimmick->Update(m_PlayerPos);
		m_GimmickCount++;
	}
}

void Map::draw(Vec2 offset)
{
	int offsetX = static_cast<int>(offset.x / 3) % Game::kScreenWidth;

	float BackGraoundPos = m_BackGroundPos.x + offsetX;

	DrawGraph(BackGraoundPos, 0, m_BackGroundHandle[m_StageNum], true);
	DrawGraph(BackGraoundPos + Game::kScreenWidth, 0, m_BackGroundHandle[m_StageNum], true);

	drawMap(offset);

	for (auto& Gimmick : m_Gimmick)
	{
		Gimmick->Draw(offset);
	}
}

void Map::PlayerMove(float knockback, float Move)
{
	m_Vec.x -= knockback;
	m_Vec.x += Move;
}

void Map::SetStage()
{
	if (m_StageNum < 4)
	{
		m_StageNum++;
	}
}

int Map::getWidth() const
{
	return kChipSize * kBgNumX[m_StageNum];
}

int Map::getHeight() const
{
	return kChipSize * kBgNumY[m_StageNum];
}

int Map::chipNumX()
{
	return (m_graphWidth / kChipSize);
}

int Map::chipNumY()
{
	return (m_graphHeight / kChipSize);
}

int Map::chipNum()
{
	return(chipNumX() * chipNumY());
}

void Map::drawMap(Vec2 offset)
{
	for (int x = 0; x < kBgNumX[m_StageNum]; x++)
	{
		for (int y = 0; y < kBgNumY[m_StageNum]; y++)
		{
			int ChipNumY = m_MapData[y][x] / kChipDivisionY;
			int ChipNumX = m_MapData[y][x] % kChipDivisionY;
			if (m_MapData[y][x] != 11 && m_MapData[y][x] != 12 &&
				m_MapData[y][x] != 27 && m_MapData[y][x] != 28)
			{
				DrawRectGraph(m_Pos.x + kChipSize * x + offset.x, m_Pos.y + kChipSize * y + offset.y,
					kChipSize * ChipNumX, kChipSize * ChipNumY,
					kChipSize, kChipSize, m_handle, true);
			}

			if (m_MapData[y][x] == 11 || m_MapData[y][x] == 12 || 
				m_MapData[y][x] == 27 || m_MapData[y][x] == 28)
			{
				if (m_BossBattle)
				{
					DrawRectGraph(m_Pos.x + kChipSize * x + offset.x, m_Pos.y + kChipSize * y + offset.y,
						kChipSize * ChipNumX, kChipSize * ChipNumY,
						kChipSize, kChipSize, m_handle, true);
				}
			}
		}
	}
}
