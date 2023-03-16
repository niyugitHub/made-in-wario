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
#include"GameOverScene.h"
#include"Option.h"
#include"SceneTitle.h"
#include "Tutorial.h"
#include"Item.h"
#include "Pad.h"
#include "GameClearScene.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
	const char* const kItemJumpFilename = "data/TwoJump.png";
	const char* const kGaugeFilename = "data/gaugeItem.png";
	const char* const kPlayerShotFilename = "data/PlayerShot.png";
	const char* const kHeartFilename = "data/heart.png";
	const char* const kAttackUpFilename = "data/sword.png";
	const char* const kOptionFilename = "data/option.png";
	const char* const kTwoJumpTutorialFilename = "data/TwoJumpTutorial.png";
	const char* const kShotTutorialFilename = "data/ShotTutorial.png";
	const char* const kDamageTutorialFilename = "data/DamageTutorial.png";

	// サウンドファイル名
	const char* const kMainbgmFilename = "sound/MainBGM.mp3";
	const char* const kBossBattleFilename = "sound/BossBattle.mp3";

	// プレイヤーの中心を少し左に寄せる
	constexpr float kPlayerPosCenter = 150.0f;

	// フェードのスピード
	constexpr int kFadeSpeed = 12;

	// チュートリアルの時間
	constexpr int kTutorialTimer = 90;
}

SceneMain::SceneMain() :
	m_PlayerPos(0, 0),
	m_EnemyPos(0, 0),
	m_MapPos(0, 0),
	m_ItemPos(2000, 800),
	m_offset(0,0),
	/*m_CollTop(false),
	m_CollBottom(false),
	m_CollLeft(false),
	m_CollRight(false),*/
	m_CollTopEnemy(false),
	m_CollBottomEnemy(false),
	m_CollLeftEnemy(false),
	m_CollRightEnemy(false),
	m_ItemNum(15),
	m_StageItemNum(3),
	m_AttackPower(10),
	m_Stage(0),
	m_Color(0),
	m_NormalSoundHandle(-1),
	m_BossSoundHandle(-1),
	m_GameOverSoundHandle(-1),
	m_Exist(true),
	m_Coll(nullptr)
{

	int sw, sh, bit;
	GetScreenState(&sw, &sh, &bit);
	m_tempScreenH = MakeScreen(sw,sh);

	assert(m_tempScreenH >= 0);

	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_player = std::make_shared<Player>();
	m_Map = std::make_shared<Map>();
	m_EnemyFactory = std::make_shared<EnemyFactory>();
	m_Coll = std::make_shared<Collision>();
	m_GameOverScene = std::make_shared<GameOverScene>();
	m_Option = std::make_shared<Option>();
	m_Tutorial = std::make_shared<Tutorial>();

	int GameClearHandle = -1;
	m_GameClearScene = std::make_shared<GameClearScene>(GameClearHandle);

	for (auto& pItemExist : m_ItemExist)
	{
		pItemExist = true;
	}

	/*for (auto& pItem : m_Item)
	{
		pItem = std::make_shared<Item>();
		pItem->SetItemType(ItemType::kAttackUp);
	}*/

	for (int i = 0; i < kItemNum; i++)
	{
		m_Item[i] = std::make_shared<Item>();
	//	m_Item[i]->SetItemNum(i);
	}


	m_player->setMap(m_Map);

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

	SetFontSize(50);
	m_func = &SceneMain::FadeinUpdate;
}

SceneMain::~SceneMain()
{
	/*delete m_player;
	m_player = nullptr;

	delete m_Map;
	m_Map = nullptr;

	delete m_Coll;
	m_Coll = nullptr;*/
	DeleteGraph(m_tempScreenH);
}

void SceneMain::init()
{
	LoadDivGraph(kPlayerGraphicFilename, Player::kCharaChipNum,
		Player::kSideCharaChipNum, Player::kColumnCharaChipNum,
		Player::kSideSize, Player::kColumnSize, m_hPlayerGraphic);

	m_OptionHandle = LoadGraph(kOptionFilename);
	m_Option->SetHandle(m_OptionHandle);
	m_TwoJumpTutorialHandle = LoadGraph(kTwoJumpTutorialFilename);
	m_ShotTutorialHandle = LoadGraph(kShotTutorialFilename);
	m_DamageTutorialHandle = LoadGraph(kDamageTutorialFilename);

	m_NormalSoundHandle = LoadSoundMem(kMainbgmFilename);
	m_BossSoundHandle = LoadSoundMem(kBossBattleFilename);

	ChangeFont("游明朝 Light");

	for (int i = 0; i < Player::kCharaChipNum; i++)
	{
		m_player->setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player->Init();
//	m_Enemy->Init();
	m_Map->load();
	m_Map->Init();

	int ItemCount = 0;
	for (auto& pItem : m_Item)
	{
		ItemCount++;
		pItem->Init(ItemCount);

		if (pItem->GetItemType() == Item::ItemType::kTwoJump)
		{
			int handle = LoadGraph(kItemJumpFilename);
			pItem->SetHandle(handle);
		}
		//攻撃力アップアイテムに当たったとき
		if (pItem->GetItemType() == Item::ItemType::kAttackUp)
		{
			int handle = LoadGraph(kAttackUpFilename);
			pItem->SetHandle(handle);
		}
		//体力アップアイテムに当たったとき
		if (pItem->GetItemType() == Item::ItemType::kHpUp)
		{
			int handle = LoadGraph(kHeartFilename);
			pItem->SetHandle(handle);
		}
		//ゲージアップアイテムに当たったとき
		if (pItem->GetItemType() == Item::ItemType::kGaugeUp)
		{
			int handle = LoadGraph(kGaugeFilename);
			pItem->SetHandle(handle);
		}
		//ショットアイテムに当たったとき
		if (pItem->GetItemType() == Item::ItemType::kShot)
		{
			int handle = LoadGraph(kPlayerShotFilename);
			pItem->SetHandle(handle);
		}
	}

 	m_EnemyFactory->Init();
	m_EnemyFactory->StageEnemy(m_Map->GetStageNum());
	m_EnemyFactory->Update();

	m_offset = { 0,Game::kScreenHeight - Map::kChipSize * Map::kBgNumY[m_Map->GetStageNum()] };
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
	if (m_TutorialCount == 0 || m_TutorialCount >= kTutorialTimer)
	{
		(this->*m_func)();
	}

	TutorialFlag();

	if (m_TutorialCount > 0 && m_TutorialCount < kTutorialTimer)
	{
		m_Color = 200;
	}
	else if(m_func == &SceneMain::NormalUpdate && !m_GameOverScene->GetActiveGameOver())
	{
		m_Color = 255;
	}

	Sound();

	if (m_GameOverScene->GetActiveGameOver())
	{
		m_Color -= 3;

		if (m_Color <= 100)
		{
			m_Color = 100;
		}
		m_GameOverScene->Update();

		if (m_GameOverScene->GetPlayAgain())
		{
			m_GameOverCount = 0;
			m_func = &SceneMain::FadeoutUpdate;
			m_GameOverScene->SetActivgeGameOver(false);
		}
		if (m_GameOverScene->GetAbort())
		{
			return (new SceneTitle);
		}
	}

	if (m_Option->GetGameEnd())
	{
		return (new SceneTitle);
	}
	
	return this;
}

void SceneMain::draw()
{
	// 加工用スクリーンハンドルをセット
	SetDrawScreen(m_tempScreenH);
	ClearDrawScreen();
//	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
//	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
//	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xff00ff, true);
	m_Map->draw(m_offset);
	m_EnemyFactory->Draw(m_offset);
	m_player->draw(m_offset);

	for (int i = (m_Map->GetStageNum()) * m_StageItemNum; i < (m_Map->GetStageNum() + 1) * m_StageItemNum; i++)
	{
		m_Item[i]->Draw(m_offset);

		//if (m_Item[i]->GetExist())
		//{
		//	/*if (m_Item[i]->GetItemType() == Item::ItemType::kTwoJump)
		//	{
		//		DrawString(m_Item[i]->GetPos().x + m_offset.x, m_Item[i]->GetPos().y, "ジャンプ", GetColor(0, 255, 0));
		//	}

		//	if (m_Item[i]->GetItemType() == Item::ItemType::kAttackUp)
		//	{
		//		DrawString(m_Item[i]->GetPos().x + m_offset.x, m_Item[i]->GetPos().y, "攻撃力アップ", GetColor(0, 255, 0));
		//	}

		//	if (m_Item[i]->GetItemType() == Item::ItemType::kHpUp)
		//	{
		//		DrawString(m_Item[i]->GetPos().x + m_offset.x, m_Item[i]->GetPos().y, "体力アップ", GetColor(0, 255, 0));
		//	}

		//	if (m_Item[i]->GetItemType() == Item::ItemType::kGaugeUp)
		//	{
		//		DrawString(m_Item[i]->GetPos().x + m_offset.x, m_Item[i]->GetPos().y, "ゲージアップ", GetColor(0, 255, 0));
		//	}*/
		//}
	}

#ifdef _DEBUG
		/*for (int i = 0; i < Map::kBgNumY; i++)
		{
			for (int j = 0; j < Map::kBgNumX; j++)
			{
				if (m_Map->GetMapData(i, j) != 0)
				{
					DrawBox(Map::kChipSize * j + m_Map->GetPosX() + m_offset.x, Map::kChipSize * i,
						Map::kChipSize * (j + 1) + m_Map->GetPosX() + m_offset.x, Map::kChipSize * (i + 1),
						0xffffff, false);
				}
			}
		}*/
#endif

	DrawTutorial();

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(m_QuakeX, 0, m_tempScreenH, false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/*for (auto& pItem : m_Item)
	{
		pItem->Draw();

#ifdef _DEBUG
		if (pItem->GetExist())
		{
			if (pItem->GetItemType() == ItemType::kTwoJump)
			{
				DrawString(pItem->GetPos().x, pItem->GetPos().y,"ジャンプ", GetColor(0, 255, 0));
			}

			if (pItem->GetItemType() == ItemType::kAttackUp)
			{
				DrawString(pItem->GetPos().x, pItem->GetPos().y, "攻撃力アップ", GetColor(0, 255, 0));
			}
		}
#endif
	}*/

	/*if (m_Enemy != nullptr)
	{
		m_Enemy->draw();
	}*/
	/*if (m_Coll->IsCollEnemy())
	{
		DrawString(0, 0, "しんだ", GetColor(0, 255, 0));
	}*/

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "敵の数:%d", m_EnemyFactory->);

	//SetDrawScreen(DX_SCREEN_BACK);
	//DrawGraph(m_QuakeX, 0, m_tempScreenH, false);
	if (SceneTutorial())
	{
		m_Tutorial->Draw();
	}
	if (m_Option->GetActiveOption())
	{
		m_Option->Draw();
	}

	if (m_GameOverScene->GetActiveGameOver())
	{
		m_GameOverScene->Draw();
	}

	// ゲームクリア時
	if (m_EnemyFactory->GetGameClear())
	{
		m_GameClearScene->Draw();
	}
}

void SceneMain::Scroll()
{
	Vec2 targetOffset{};

	// スクロールの計算 プレイヤーが画面中央に表示されるようスクロールする
	targetOffset.x = (Game::kScreenWidth / 2 - kPlayerPosCenter) - m_player->GetPos().x;
	targetOffset.y = (Game::kScreenHeight / 2) - m_player->GetPos().y;
	if (!m_EnemyFactory->GetBossBattle())
	{
		m_Map->SetBossBattle(false);
		if (targetOffset.x > 0)
		{
			targetOffset.x = 0;
		}
		if (targetOffset.x < -m_Map->getWidth() + Game::kScreenWidth)
		{
			targetOffset.x = -m_Map->getWidth() + Game::kScreenWidth;
		}

		if (targetOffset.y > 0)
		{
			targetOffset.y = 0;
		}
		if (targetOffset.y < -m_Map->getHeight() + Game::kScreenHeight)
		{
			targetOffset.y = -m_Map->getHeight() + Game::kScreenHeight;
		}
		
		m_offset = targetOffset * 0.2f + m_offset * 0.8f;
	}

	if (m_EnemyFactory->GetBossBattle())
	{
		m_Map->SetBossBattle(true);
		if (targetOffset.x > -4672)
		{
			targetOffset.x = -4672;
		}
		if (targetOffset.x < -3136)
		{
			targetOffset.x = -3136;
		}
		
			targetOffset.y = -1792;
		
		m_offset = targetOffset * 0.2f + m_offset * 0.8f;
	}
}

void SceneMain::IsItemPosition(int StageNum)
{
	m_Stage = StageNum;
}

void SceneMain::InitPlayerPos()
{
	if (m_Map->GetStageNum() == 0)
	{
		m_PlayerPos = { 200, 1000 };
		m_offset = { 0,-192};
	}

	if (m_Map->GetStageNum() == 1)
	{
		m_PlayerPos = { 0,Map::kChipSize * 56 };
		m_offset = { 0,Game::kScreenHeight - Map::kChipSize * Map::kBgNumY[m_Map->GetStageNum()] };
	}

	if (m_Map->GetStageNum() == 2)
	{
		m_PlayerPos = { 0,Map::kChipSize * 6 };
		m_offset = { 0,0};
	}

	m_player->SetPos(m_PlayerPos);
}

bool SceneMain::SceneTutorial()
{
	/*if (m_Tutorial->GetJumpFlag() && !m_Tutorial->GetPastJumpFlag())
	{
		return true;
	}

	if (m_Tutorial->GetAttackFlag() && !m_Tutorial->GetPastAttackFlag())
	{
		return true;
	}

	if (m_Tutorial->GetDashFlag() && !m_Tutorial->GetPastDashJFlag())
	{
		return true;
	}*/

	if (m_Tutorial->GetTwoJumpFlag() && !m_Tutorial->GetPastTwoJumpFlag())
	{
		return true;
	}

	if (m_Tutorial->GetShotFlag() && !m_Tutorial->GetPastShotFlag())
	{
		return true;
	}
	if (m_Tutorial->GetDamageFlag() && !m_Tutorial->GetPastDamageFlag())
	{
		return true;
	}

	/*if (m_Tutorial->GetAttackUpFlag() && !m_Tutorial->GetPastAttackUpFlag())
	{
		return true;
	}

	if (m_Tutorial->GetHpUpFlag() && !m_Tutorial->GetPastHpUpFlag())
	{
		return true;
	}

	if (m_Tutorial->GetGaugeUpFlag() && !m_Tutorial->GetPastGaugeUpFlag())
	{
		return true;
	}*/

	return false;
}

void SceneMain::DrawTutorial()
{
	if (m_Tutorial->GetJumpFlag() && !m_Tutorial->GetPastJumpFlag())
	{
		DrawString(Game::kScreenWidth / 2, 400,"A:ジャンプ", 0x00ff00);
	}

	if (m_Tutorial->GetAttackFlag() && !m_Tutorial->GetPastAttackFlag())
	{
		DrawString(Game::kScreenWidth / 2, 400, "RB,LB:攻撃", 0x00ff00);
	}
	if (m_Tutorial->GetDashFlag() && !m_Tutorial->GetPastDashFlag())
	{
		DrawString(Game::kScreenWidth / 2, 400, "A:ジャンプ\nXダッシュ", 0x00ff00);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_StringColor);
	if (m_Tutorial->GetAttackUpFlag() && m_StringColor > 0)
	{
		DrawString(m_PlayerPos.x + m_offset.x, m_PlayerPos.y + m_offset.y - 50 + (m_StringColor / 2), "攻撃力Up", 0x00ff00);
	}

	if (m_Tutorial->GetHpUpFlag() && m_StringColor > 0)
	{
		DrawString(m_PlayerPos.x + m_offset.x, m_PlayerPos.y + m_offset.y - 50 + (m_StringColor / 2), "体力UP", 0x00ff00);
	}

	if (m_Tutorial->GetGaugeUpFlag() && m_StringColor > 0)
	{
		DrawString(m_PlayerPos.x + m_offset.x, m_PlayerPos.y + m_offset.y- 50 + (m_StringColor / 2), "ゲージUP", 0x00ff00);
	}

	m_StringColor -= 5;

	if (m_StringColor <= 0)
	{
		m_Tutorial->SetAttackUpFlag(false);
		m_Tutorial->SetHpUpFlag(false);
		m_Tutorial->SetGaugeUpFlag(false);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	if (m_Tutorial->GetTwoJumpFlag() && !m_Tutorial->GetPastTwoJumpFlag())
	{
		DrawGraph(0, 0, m_OptionHandle, true);
	}

	if (m_Tutorial->GetShotFlag() && !m_Tutorial->GetPastShotFlag())
	{
		DrawGraph(0, 0, m_OptionHandle, true);
	}

	if (m_Tutorial->GetDamageFlag() && !m_Tutorial->GetPastDamageFlag())
	{
		DrawGraph(0, 0, m_OptionHandle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_Tutorial->GetTwoJumpFlag() && !m_Tutorial->GetPastTwoJumpFlag())
	{
		DrawGraph(0, 0, m_TwoJumpTutorialHandle, true);
	}

	if (m_Tutorial->GetShotFlag() && !m_Tutorial->GetPastShotFlag())
	{
		DrawGraph(0, 0, m_ShotTutorialHandle, true);
	}

	if (m_Tutorial->GetDamageFlag() && !m_Tutorial->GetPastDamageFlag())
	{
		DrawGraph(0, 0, m_DamageTutorialHandle, true);
	}
}

void SceneMain::TutorialFlag()
{
	if (m_Map->GetStageNum() == 0 && m_PlayerPos.x >= 1600 && !m_Tutorial->GetPastJumpFlag())
	{
		m_Tutorial->SetFlag(true,Tutorial::kJumpFlag);
		m_TutorialCount++;
	}
	if (m_PlayerPos.x >= 2000 && !m_Tutorial->GetPastJumpFlag())
	{
		m_Tutorial->SetPastJumpFlag(true);
		m_TutorialCount = 0;
	}

	if (m_Map->GetStageNum() == 0 && m_PlayerPos.x >= 2700 && !m_Tutorial->GetPastDashFlag())
	{
		m_Tutorial->SetFlag(true, Tutorial::kDashFlag);
		m_TutorialCount++;
	}

	if (m_PlayerPos.x >= 3200 && !m_Tutorial->GetPastDashFlag())
	{
		m_Tutorial->SetPastDashFlag(true);
		m_TutorialCount = 0;
	}

	if (m_Tutorial->GetAttackFlag() && !m_Tutorial->GetPastAttackFlag())
	{
		m_TutorialCount++;
		if (Pad::isTrigger(PAD_INPUT_5) || Pad::isTrigger(PAD_INPUT_6))
		{
			m_Tutorial->SetPastAttackFlag(true);
			m_TutorialCount = 0;
		}
	}
}

void SceneMain::Sound()
{
	if (!CheckSoundMem(m_NormalSoundHandle) && !m_EnemyFactory->GetBossBattle())
	{
		StopSoundMem(m_BossSoundHandle);
		PlaySoundMem(m_NormalSoundHandle, DX_PLAYTYPE_BACK);
	}

	if (!CheckSoundMem(m_BossSoundHandle) && m_EnemyFactory->GetBossBattle())
	{
		StopSoundMem(m_NormalSoundHandle);
		PlaySoundMem(m_BossSoundHandle, DX_PLAYTYPE_BACK);
	}
}

void SceneMain::FadeinUpdate()
{
	m_Color += kFadeSpeed;
	if (m_Color >= 255)
	{
		m_Color = 255;
		m_func = &SceneMain::NormalUpdate;
	}
}

void SceneMain::NormalUpdate()
{
	if (m_player->GetDamage())
	{
		m_QuakeFrame = 30;
		m_QuakeX = 20;
		m_player->SetDamage(false);
	}

	if (m_QuakeFrame > 0)
	{
		m_QuakeX = -m_QuakeX;
		m_QuakeX *= 0.95;
		m_QuakeFrame--;

		if (m_QuakeFrame == 0)
		{
			m_QuakeX = 0;
		}
	}
	if (m_player->GetStageClaer())
	{
		/*m_player->SetStageClaer(false);*/
		/*m_Map->SetStage();*/
		m_func = &SceneMain::FadeoutUpdate;
	}
	if (!m_player->GetExist())
	{
		/*if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_func = &SceneMain::FadeoutUpdate;
		}*/
		if (!m_GameOverScene->GetActiveGameOver())
		{
			m_GameOverCount++;
		}

		if (m_GameOverCount >= 70 && !m_GameOverScene->GetActiveGameOver())
		{
			m_GameOverScene->Init();
		}
	}

	m_Coll->Update();

	m_Map->update();

	m_player->update();

	Scroll();

	m_PlayerPos = m_player->GetPos();

	IsItemPosition(1);

	if (m_player->GetExist())
	{
		for (int i = (m_Map->GetStageNum()) * m_StageItemNum; i < (m_Map->GetStageNum() + 1) * m_StageItemNum; i++)
		{
			if (m_Item[i]->GetExist())
			{
				m_Item[i]->Update();
				m_Coll->setItem(m_Item[i]);
				//ジャンプアイテムに当たったとき
				if (m_Coll->IsCollItem() && m_Item[i]->GetItemType() == Item::ItemType::kTwoJump)
				{
					m_player->SetCollItemTwoJump(true);
					m_ItemExist[i] = false;
					m_Item[i]->SetExist(m_ItemExist[i]);
					m_Tutorial->SetFlag(true, Tutorial::kTwoJumpFlag);
				}
				//攻撃力アップアイテムに当たったとき
				if (m_Coll->IsCollItem() && m_Item[i]->GetItemType() == Item::ItemType::kAttackUp)
				{
					m_AttackPower += 10;
					m_player->SetAttackPower(m_AttackPower);
					m_ItemExist[i] = false;
					m_Item[i]->SetExist(m_ItemExist[i]);
					m_Tutorial->SetFlag(true, Tutorial::kAttackUpFlag);
					m_StringColor = 255;
				}
				//体力アップアイテムに当たったとき
				if (m_Coll->IsCollItem() && m_Item[i]->GetItemType() == Item::ItemType::kHpUp)
				{
					m_Item[i]->SetExist(false);
					m_player->MaxHpUp();
					m_Tutorial->SetFlag(true, Tutorial::kHpUpFlag);
					m_StringColor = 255;
				}
				//ゲージアップアイテムに当たったとき
				if (m_Coll->IsCollItem() && m_Item[i]->GetItemType() == Item::ItemType::kGaugeUp)
				{
					m_Item[i]->SetExist(false);
					m_player->MaxGaugeUp();
					m_Tutorial->SetFlag(true, Tutorial::kGaugeUpFlag);
					m_StringColor = 255;
				}
				//ショットアイテムに当たったとき
				if (m_Coll->IsCollItem() && m_Item[i]->GetItemType() == Item::ItemType::kShot)
				{
					m_Item[i]->SetExist(false);
					m_player->SetShot(true);
					m_Tutorial->SetFlag(true, Tutorial::kShotFlag);
				}
			}
		}
	}

	m_Coll->InitColl();

	m_EnemyFactory->Update();

	if (m_EnemyFactory->GetAttackTutorialFlag())
	{
		m_Tutorial->SetFlag(true, Tutorial::kAttackFlag);
	}

	if (m_EnemyFactory->GetDamageFlag())
	{
		m_Tutorial->SetFlag(true, Tutorial::kDamageFlag);
	}

	if (SceneTutorial())
	{
		m_func = &SceneMain::TutorialUpdate;
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_Option->Init();
		m_func = &SceneMain::OptionUpdate;
	}

	// ゲームクリア時
	if (m_EnemyFactory->GetGameClear())
	{
		m_GameClearScene->Update();
		m_Color = 200;
	}
}

void SceneMain::FadeoutUpdate()
{
	m_Color -= 9;
	if (m_Color <= 0)
	{
		m_offset = { 0,0 };
		InitPlayerPos();
		m_player->SetPos(m_PlayerPos);
		
		m_PlayerPos.x = 0;

		if (m_player->GetExist())
		{
			m_player->SetStageClaer(false);
			m_Map->SetStage();
			m_Map->Init();
			InitPlayerPos();
			m_player->SetPos(m_PlayerPos);
			m_EnemyFactory->EnemyDead();
			m_EnemyFactory->StageEnemy(m_Map->GetStageNum());
			m_EnemyFactory->Update();
			/*m_player->SetPos(m_PlayerPos);*/

			m_Color = 0;
		}

		if (!m_player->GetExist())
		{

			m_player->NotExist();
			m_Map->Init();
			m_Map->SetMap(m_MapPos);
			m_Exist = true;
			m_player->SetExist(m_Exist);

			m_Coll->setEnemy(m_EnemyFactory);
			m_EnemyFactory->EnemyDead();
			m_EnemyFactory->StageEnemy(m_Map->GetStageNum());
			m_EnemyFactory->Update();
		}
		/*m_offset = { 0,Game::kScreenHeight - Map::kChipSize * Map::kBgNumY[m_Map->GetStageNum()] };*/

		m_func = &SceneMain::FadeinUpdate;
	}
}

void SceneMain::OptionUpdate()
{
	m_Color = 230;
	m_Option->Update();

	if (!m_Option->GetActiveOption())
	{
		m_func = &SceneMain::NormalUpdate;
		m_Color = 255;
	}
}

void SceneMain::TutorialUpdate()
{
	m_Tutorial->Update();

	if (!SceneTutorial())
	{
		m_func = &SceneMain::NormalUpdate;
	}
}
