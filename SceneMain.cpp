#include <DxLib.h>
#include "SceneMain.h"
#include"Player.h"
#include"Map.h"
#include"game.h"
#include"Vec2.h"
#include"Collision.h"
#include"EnemyBase.h"


namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
}

SceneMain::SceneMain() :
	m_PlayerPos(0, 0),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollLeft(false),
	m_CollRight(false),
	m_DeadPlayer(false),
	m_Coll(nullptr)
{
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_player = new Player;
	m_Map = new Map;
	m_Enemy = new EnemyBase;

	m_Coll = new Collision;

	m_Coll->setPlayer(m_player);
	m_Coll->setMap(m_Map);
	m_Coll->setEnemy(m_Enemy);
	m_Enemy->SetMap(m_Map);
}
SceneMain::~SceneMain()
{
	delete m_player;
	m_player = nullptr;

	delete m_Map;
	m_Map = nullptr;

	delete m_Coll;
	m_Coll = nullptr;
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
	m_Enemy->Init();
	m_Map->load();
}

void SceneMain::end()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	m_Map->unload();
	m_Enemy->end();
}

SceneBase* SceneMain::update()
{
	if (m_Coll->FallPlayer())
	{
 		m_DeadPlayer = true;
	}

	if (m_DeadPlayer)
	{

	}

	if (!m_DeadPlayer)
	{
		m_PlayerPos = m_player->GetPos();

	//	IsCollision();

		m_Coll->Update();

		m_CollTop = m_Coll->IsCollTop();
		m_CollBottom = m_Coll->IsCollBottom();
		m_CollRight = m_Coll->IsCollRight();
		m_CollLeft = m_Coll->IsCollLeft();

		m_player->SetCollTop(m_CollTop);
		m_player->SetCollBottom(m_CollBottom);

		m_Map->SetCollRight(m_CollRight);
		m_Map->SetCollLeft(m_CollLeft);

	//	m_PlayerPos = m_player->GetPos();

		m_player->update();
		m_Enemy->update();

		m_Map->update();

		m_Coll->InitColl();


	}
		
	return this;
}

void SceneMain::draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	m_Map->draw();
	m_player->draw();
	m_Enemy->draw();
	if (m_Coll->IsCollEnemy())
	{
		DrawString(0, 0, "当たってる", GetColor(0, 255, 0));
	}
}

// ブロックとプレイヤーの当たり判定
void SceneMain::IsCollision()
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

	for(int i = 0; i < Map::kBgNumY; i++)
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
					m_PlayerPos.y = i * Map::kChipSize - (Player::kColumnSize) + 1;
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

void SceneMain::isInitColl()
{
	m_CollTop = false;
	m_CollBottom = false;
	m_CollRight = false;
	m_CollLeft = false;
}
