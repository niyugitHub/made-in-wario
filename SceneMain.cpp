#include <DxLib.h>
#include<cassert>
#include "SceneMain.h"
#include"Player.h"
#include"Map.h"
#include"game.h"
#include"Vec2.h"
#include"Collision.h"
#include"EnemyBase.h"
#include"Enemy1.h"
#include"EnemyFactory.h"


namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
}

SceneMain::SceneMain() :
	m_PlayerPos(0, 0),
	m_EnemyPos(0,0),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollLeft(false),
	m_CollRight(false),
	m_CollTopEnemy(false),
	m_CollBottomEnemy(false),
	m_CollLeftEnemy(false),
	m_CollRightEnemy(false),
	m_DeadPlayer(false),
	m_Coll(nullptr)
{
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_player = std::make_shared<Player>();
	m_Map = std::make_shared<Map>();
	m_Enemy = std::make_shared<Enemy1>();
	m_EnemyFactory = std::make_shared<EnemyFactory>();
	m_Coll = std::make_shared<Collision>();


	m_Coll->setPlayer(m_player);
	m_Coll->setMap(m_Map);
	m_Coll->setEnemy(m_Enemy);
	m_Enemy->SetMap(m_Map);
	m_Enemy->SetPlayer(m_player);
	m_EnemyFactory->SetPlayer(m_player);
	m_EnemyFactory->SetMap(m_Map);
	m_EnemyFactory->SetColl(m_Coll);
}
SceneMain::~SceneMain()
{
	/*delete m_player;
	m_player = nullptr;

	delete m_Map;
	m_Map = nullptr;

	delete m_Coll;
	m_Coll = nullptr;*/
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

	m_EnemyFactory->Update();

	if (!m_DeadPlayer)
	{
		m_PlayerPos = m_player->GetPos();
	//	IsCollision();

		m_Coll->Update();

		// プレイヤーとマップの当たり判定
		m_CollTop = m_Coll->IsCollTop();
		m_CollBottom = m_Coll->IsCollBottom();
		m_CollRight = m_Coll->IsCollRight();
		m_CollLeft = m_Coll->IsCollLeft();

		m_player->SetCollTop(m_CollTop);
		m_player->SetCollBottom(m_CollBottom);
		m_Map->SetCollRight(m_CollRight);
		m_Map->SetCollLeft(m_CollLeft);

		m_player->update();
		

		m_Map->update();

		m_Coll->InitColl();
	}

	if (m_Enemy != nullptr)
	{
		m_Enemy->update();
		m_EnemyPos = m_Enemy->GetPos();

		m_Coll->Update();

		// エネミーとマップの当たり判定
		m_CollTopEnemy = m_Coll->IsCollTopEnemy();
		m_CollBottomEnemy = m_Coll->IsCollBottomEnemy();
		m_CollRightEnemy = m_Coll->IsCollRightEnemy();
		m_CollLeftEnemy = m_Coll->IsCollLeftEnemy();

		m_Enemy->SetCollTop(m_CollTopEnemy);
		m_Enemy->SetCollBottom(m_CollBottomEnemy);
		m_Enemy->SetCollRight(m_CollRightEnemy);
		m_Enemy->SetCollLeft(m_CollLeftEnemy);

		if (m_Coll->IsCollAttackPlayer())
		{
			m_Enemy->setExist(false);
		}

		m_Coll->InitColl();
	}
		
	return this;
}

void SceneMain::draw()
{
//	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	m_Map->draw();
	m_EnemyFactory->Draw();
	m_player->draw();

	if (m_Enemy != nullptr)
	{
		m_Enemy->draw();
	}
	if (m_Coll->IsCollEnemy())
	{
		DrawString(0, 0, "しんだ", GetColor(0, 255, 0));
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "敵の数:%d", m_EnemyFactory->);
}
