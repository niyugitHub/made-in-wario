#include<Dxlib.h>

#include "Minigame1.h"
#include "game.h"

namespace
{
	// 入出力ファイル名
	const char* const kFileName = "data/Assets(64×64).png";

	// チップの数
	static constexpr int kBgNumY = 17;
	static constexpr int kBgNumX = 30;

	// マップデータ
	constexpr int kMapData[kBgNumY][kBgNumX] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28},
		{28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28},
		{28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28},
		{28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28},
	};
}

Minigame1::Minigame1() :
	m_handle(-1),
	m_graphWidth(0),
	m_graphHeight(0)
{
	for (int i = 0; i < kBgNumY; i++)
	{
		for (int j = 0; j < kBgNumX; j++)
		{
			m_MapData[i][j] = kMapData[i][j];
		}
	}
}

Minigame1::~Minigame1()
{
}

void Minigame1::load()
{
	m_handle = LoadGraph(kFileName);
	GetGraphSize(m_handle, &m_graphWidth, &m_graphHeight);
}

void Minigame1::unload()
{
	DeleteGraph(m_handle);
}

void Minigame1::update()
{
	
}

void Minigame1::draw()
{
	drawMap();
}

int Minigame1::chipNumX()
{
	return (m_graphWidth / kChipSize);
}

int Minigame1::chipNumY()
{
	return (m_graphHeight / kChipSize);
}

int Minigame1::chipNum()
{
	return(chipNumX() * chipNumY());
}

void Minigame1::drawMap()
{
	for (int x = 0; x < kBgNumX; x++)
	{
		for (int y = 0; y < kBgNumY; y++)
		{
			int ChipNumY = kMapData[y][x] / 25;
			int ChipNumX = kMapData[y][x] % 25;
			DrawRectGraph(x * kChipSize, y * kChipSize,
				kChipSize * ChipNumX, kChipSize * ChipNumY,
				kChipSize, kChipSize, m_handle, true);
		}
	}
}
