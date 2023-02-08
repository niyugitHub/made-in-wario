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
#include"Item.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
}

SceneMain::SceneMain() :
	m_PlayerPos(0, 0),
	m_EnemyPos(0, 0),
	m_MapPos(0, 0),
	m_ItemPos(500, 800),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollLeft(false),
	m_CollRight(false),
	m_CollTopEnemy(false),
	m_CollBottomEnemy(false),
	m_CollLeftEnemy(false),
	m_CollRightEnemy(false),
	m_ItemNum(25),
	m_StageItemNum(5),
	m_AttackPower(10),
	m_Exist(true),
	m_Coll(nullptr)
{
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_player = std::make_shared<Player>();
	m_Map = std::make_shared<Map>();
//	m_Enemy = std::make_shared<Enemy1>();
	m_EnemyFactory = std::make_shared<EnemyFactory>();
	m_Coll = std::make_shared<Collision>();

	for (auto& pItemExist : m_ItemExist)
	{
		pItemExist = true;
	}

	for (auto& pItem : m_Item)
	{
		pItem = std::make_shared<Item>();
		pItem->SetItemType(ItemType::kAttackUp);
	}

	for (int i = 0; i < kItemNum; i++)
	{
		/*m_Item[i] = std::make_shared<Item>();*/
		m_Item[0]->SetPos(m_ItemPos);
		m_Item[0]->SetItemType(ItemType::kTwoJump);
	}

	m_Map->setPlayer(m_player);

	m_Coll->setPlayer(m_player);
	m_Coll->setMap(m_Map);
	m_Coll->setEnemy(m_EnemyFactory);
//	m_Coll->setItem(m_Item);

	for (auto& pItem : m_Item)
	{
		m_Coll->setItem(pItem);
	}
 
//	m_Enemy->SetMap(m_Map);
//	m_Enemy->SetPlayer(m_player);
	m_EnemyFactory->SetPlayer(m_player);
	m_EnemyFactory->SetMap(m_Map);
	m_EnemyFactory->SetColl(m_Coll);
//	m_Item->SetMap(m_Map);
	for (auto& pItem : m_Item)
	{
		pItem->SetMap(m_Map);
	}
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
//	m_Enemy->Init();
	m_Map->load();
//	m_Item->Init();
	for (auto& pItem : m_Item)
	{
		pItem->Init();
	}
}

void SceneMain::end()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	m_Map->unload();
//	m_Enemy->end();
}

SceneBase* SceneMain::update()
{
	if (!m_Exist)
	{
		m_Map->SetMap(m_MapPos);
		m_PlayerPos.y = 500;
		m_PlayerPos.x = 500;
		m_player->SetPos(m_PlayerPos);
		m_Exist = true;
		m_player->SetExist(m_Exist);
	}

	if (m_Coll->FallPlayer())
	{
		m_Exist = false;
		m_player->SetExist(m_Exist);
	}
	/*m_EnemyFactory->Update();*/

	/*if (!m_DeadPlayer)
	{*/
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
		/*m_Item->Update();*/

		/*for (auto& pItem : m_Item)
		{
			pItem->Update();
			m_Coll->setItem(pItem);

			if (m_Coll->IsCollItem() && pItem->GetItemType() == ItemType::kTwoJump)
			{
				m_player->SetCollItemTwoJump(true);
			}

			if (m_Coll->IsCollItem() && pItem->GetItemType() == ItemType::kAttackUp)
			{
				m_AttackPower += 10;
				m_player->SetAttackPower(m_AttackPower);
			}
		}*/

		for (int i = 0; i < kItemNum; i++)
		{
			if (m_ItemExist[i])
			{
				m_Item[i]->Update();
				m_Coll->setItem(m_Item[i]);

				if (m_Coll->IsCollItem() && m_Item[i]->GetItemType() == ItemType::kTwoJump)
				{
					m_player->SetCollItemTwoJump(true);
 					m_ItemExist[i] = false;
					m_Item[i]->SetExist(m_ItemExist[i]);
				}

				if (m_Coll->IsCollItem() && m_Item[i]->GetItemType() == ItemType::kAttackUp)
				{
					m_AttackPower += 10;
					m_player->SetAttackPower(m_AttackPower);
					m_ItemExist[i] = false;
					m_Item[i]->SetExist(m_ItemExist[i]);
				}
			}
		}

		m_Coll->InitColl();
	//}

	m_EnemyFactory->Update();

	/*if (m_Coll->IsCollItem())
	{
		m_player->SetCollItemTwoJump(true);
	}*/

	//if (m_Enemy != nullptr)
	//{
	//	m_Enemy->update();
	//	m_EnemyPos = m_Enemy->GetPos();

	//	m_Coll->Update();

	//	// エネミーとマップの当たり判定
	//	m_CollTopEnemy = m_Coll->IsCollTopEnemy();
	//	m_CollBottomEnemy = m_Coll->IsCollBottomEnemy();
	//	m_CollRightEnemy = m_Coll->IsCollRightEnemy();
	//	m_CollLeftEnemy = m_Coll->IsCollLeftEnemy();

	//	m_Enemy->SetCollTop(m_CollTopEnemy);
	//	m_Enemy->SetCollBottom(m_CollBottomEnemy);
	//	m_Enemy->SetCollRight(m_CollRightEnemy);
	//	m_Enemy->SetCollLeft(m_CollLeftEnemy);

	//	if (m_Coll->IsCollAttackPlayer())
	//	{
	//		m_Enemy->setExist(false);
	//	}

	//	m_Coll->InitColl();
	//}
		
	return this;
}

void SceneMain::draw()
{
//	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	m_Map->draw();
	m_EnemyFactory->Draw();
	m_player->draw();
//	m_Item->Draw();

	for (auto& pItem : m_Item)
	{
		pItem->Draw();

		if (pItem->GetItemType() == ItemType::kTwoJump)
		{
			DrawString(pItem->GetPos().x, pItem->GetPos().y,"ジャンプ", GetColor(0, 255, 0));
		}

		if (pItem->GetItemType() == ItemType::kAttackUp)
		{
			DrawString(pItem->GetPos().x, pItem->GetPos().y, "攻撃力アップ", GetColor(0, 255, 0));
		}
	}

	/*if (m_Enemy != nullptr)
	{
		m_Enemy->draw();
	}*/
	/*if (m_Coll->IsCollEnemy())
	{
		DrawString(0, 0, "しんだ", GetColor(0, 255, 0));
	}*/

	if (m_Coll->IsCollItem())
	{
		DrawString(300, 0, "aafakla", GetColor(0, 255, 0));
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "敵の数:%d", m_EnemyFactory->);
}

void SceneMain::IsItemPosition()
{
}
