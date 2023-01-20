#include <DxLib.h>
#include "SceneMain.h"
#include"Player.h"
#include"Minigame1.h"
#include"Vec2.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
}

SceneMain::SceneMain() : 
	m_PlayerPos(0,0)
{
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_player = new Player;
	m_Map = new Minigame1;
}
SceneMain::~SceneMain()
{
	m_player = nullptr;
	delete m_player;
}

void SceneMain::init()
{
	LoadDivGraph(kPlayerGraphicFilename, Player::kCharaChipNum,
		Player::kSideCharaChipNum, Player::kColumnCharaChipNum,
		Player::kSideSize, Player::kColumnSize, m_hPlayerGraphic);

	for (int i = 0; i < Player::kCharaChipNum; i++)
	{
		m_player->setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player->Init();
	m_Map->load();
}

void SceneMain::end()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	m_Map->unload();
}

SceneBase* SceneMain::update()
{
	if (!Collision())
	{
		m_player->update();
	}
	m_PlayerPos = m_player->GetPos();


	return this;
}

void SceneMain::draw()
{
	m_Map->draw();
	m_player->draw();
}

// ブロックとプレイヤーの当たり判定
bool SceneMain::Collision()
{
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
			MapNum[i][j] = m_Map->GetMapData(i, j);
			if (MapNum[i][j] != 0)
			{
				//下
				if (m_PlayerPos.y + Player::kColumnSize < i * Minigame1::kChipSize)
				{
					continue;
				}
				//上
				if (m_PlayerPos.y + 20 > i * Minigame1::kChipSize + Minigame1::kChipSize)
				{
					continue;
				}
				//右
				if (m_PlayerPos.x + Player::kSideSize - 40 < j * Minigame1::kChipSize)
				{
					continue;
				}
				//左
				if (m_PlayerPos.x > j * Minigame1::kChipSize + Minigame1::kChipSize / 2)
				{
					continue;
				}
				return true;
			}
		}
	}

	return false;
}
