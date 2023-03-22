#include "Collision.h"
#include "EnemyFactory.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "BossEnemy.h"
#include "BossEnemy2.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include "Particle.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	// グラフィックファイル名
	const char* const kEnemyGraphicFilename = "data/Enemy.png";
	const char* const kShotGraphicFilename = "data/Shot.png";

	// サウンドファイル名
	const char* const kPlayerSoundDamageFilename = "sound/Damage.mp3";
	const char* const kPlayerSoundHitAttackFilename = "sound/HitAttack.mp3";

}

EnemyFactory::EnemyFactory() : 
	m_EnemyName(kNormal),
	m_Frame(0),
	m_handle(-1),
	m_Shothandle(-1),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollRight(false),
	m_CollLeft(false),
	m_Pos(0,0),
	m_ThrowPos(0,0),
	m_Particle(std::make_shared<Particle>())
{
//	m_Coll = std::make_shared<Collision>();
}

EnemyFactory::~EnemyFactory()
{
}

void EnemyFactory::Init()
{
	m_handle = LoadGraph(kEnemyGraphicFilename);
	m_Shothandle = LoadGraph(kShotGraphicFilename);

	m_SoundDamage = LoadSoundMem(kPlayerSoundDamageFilename);
	m_SoundHitAttack = LoadSoundMem(kPlayerSoundHitAttackFilename);
}

void EnemyFactory::end()
{
}

void EnemyFactory::Update()
{
	//m_Coll->InitColl();
	/*m_Frame++;

	if (m_Frame == 1)
	{
		Create(kJump, { 1500,600 });
	}*/

//	Stage1Enemy();
	//いなくなった敵は消えてもらう
	//消す命令のくせに、実際には決してなくて、後ろによけてるだけ
	//auto rmIt = std::remove_if(//条件に合致したものを消す
	//	m_Enemy.begin(),	//対象はm_Enemyの最初から
	//	m_Enemy.end(),		//最後まで
	//	//消えてもらう条件を表すラムダ式
	//	//trueだと消える。falseだと消えない
	//	[](const std::shared_ptr<EnemyBase>& enemy) {
	//		return !enemy->isExist();
	//	});

	////実際に範囲を指定して消す
	//m_Enemy.erase(rmIt, m_Enemy.end());
	////ここまでやらないと実際には消えないので注意

	for (auto& enemy : m_Enemy)
	{
		if (!m_Player->GetInitAttack())
		{
			enemy->SetHit(false);
		}
	}
	
	m_Particle->Update();

	for (auto& enemy : m_Enemy)
	{
		enemy->update();

		m_CentorPos = (enemy->GetCentorPos());

		if (enemy->GetHit())
		{
			enemy->KnockBack();
		}

		if (enemy->isExist())
		{
			m_Coll->InitColl();

			
			/*enemy->update();*/

			m_Pos = enemy->GetPos();
			m_ThrowPos = enemy->GetThrowPos();
			m_EnemySize1 = enemy->GetGraphSize1();
			m_EnemySize2 = enemy->GetGraphSize2();

			m_Coll->Update();

			//// エネミーの攻撃があたった＆プレイヤーの無敵時間が０以下の時
			//if (enemy->CollThrow() && m_Player->GetNoDamageFrame() <= 0)
			//{
			////	DrawString(500, 0, "しんだ", GetColor(100, 255, 100));
			//	m_Player->Ondamage();
			//	m_Player->SetNoDamageFrame(100);
			//	m_Player->SetEnemyPos(m_Pos);
			//	m_Player->SetKnockBackSpeed(Player::kKnockBackSpeed);
			////	m_Player->IsKnockBack(m_Pos);
			//}

			// エネミーの攻撃があたった＆プレイヤーの無敵時間が０以下の時
			if (m_Coll->IsCollEnemy() && enemy->isExist() && m_Player->GetNoDamageFrame() <= 0)
			{
			//	DrawString(500, 0, "しんだ", GetColor(100, 255, 100));
				m_DamageFlag = true;
				m_Player->Ondamage();
				m_Player->SetNoDamageFrame(100);
				m_Player->SetKnockBackSpeed(Player::kKnockBackSpeed);
				m_Player->SetEnemyPos(enemy->GetCentorPos());
				PlaySoundMem(m_SoundDamage, DX_PLAYTYPE_BACK);
			}

			// エネミーとマップの当たり判定
			m_CollTop = m_Coll->IsCollTopEnemy();
			m_CollBottom = m_Coll->IsCollBottomEnemy();
			m_CollRight = m_Coll->IsCollRightEnemy();
			m_CollLeft = m_Coll->IsCollLeftEnemy();

			enemy->SetCollTop(m_CollTop);
			enemy->SetCollBottom(m_CollBottom);
			enemy->SetCollRight(m_CollRight);
			enemy->SetCollLeft(m_CollLeft);

			enemy->SetPos(m_Pos);

			// プレイヤーの攻撃が敵に当たった時
			if (m_Coll->IsCollAttackPlayer() && !enemy->GetHit())
			{
				
				m_Player->IsGauge();
				m_Player->SetEnemyPos(enemy->GetCentorPos());
				m_Player->SetKnockBackSpeed(Player::kHitKnockBackSpeed);
				m_Particle->SetEnemyPos(enemy->GetCentorPos());
				m_Particle->SetEnemyParticle();
				enemy->SetHit(true);
				enemy->OnDamage(m_Player->GetAttackPower());
				enemy->InitKnockBack();
				PlaySoundMem(m_SoundHitAttack, DX_PLAYTYPE_BACK);
			}

			// プレイヤーのショットが敵に当たった時
			if (enemy->CollShotPlayer() && !enemy->GetHit())
			{
				m_Player->SetEnemyPos(enemy->GetCentorPos());
				m_Particle->SetEnemyPos(enemy->GetCentorPos());
				m_Particle->SetEnemyParticle();
				enemy->SetHit(true);
				enemy->OnShotDamage(m_Player->GetAttackPower());
				enemy->InitKnockBack();
				PlaySoundMem(m_SoundHitAttack, DX_PLAYTYPE_BACK);
			}

			/*if (enemy->GetHit())
			{
				enemy->KnockBack();
			}*/
		}

		// エネミーの攻撃があたった＆プレイヤーの無敵時間が０以下の時
		if (enemy->CollThrow() && m_Player->GetNoDamageFrame() <= 0)
		{
			m_DamageFlag = true;
			m_Player->Ondamage();
			m_Player->SetNoDamageFrame(100);
			m_Player->SetKnockBackSpeed(Player::kKnockBackSpeed);
			m_Player->SetEnemyPos(enemy->GetCentorPos());
			PlaySoundMem(m_SoundDamage, DX_PLAYTYPE_BACK);
			//	m_Player->IsKnockBack(m_Pos);
		}

		// トゲがプレイヤーに当たった＆プレイヤーの無敵時間が０以下の時
		if (m_Player->CollNeedle() && m_Player->GetNoDamageFrame() <= 0)
		{
			m_DamageFlag = true;
			m_Player->Ondamage();
			PlaySoundMem(m_SoundDamage, DX_PLAYTYPE_BACK);
		}
	}
}

void EnemyFactory::Draw(Vec2 offset)
{
	for (auto& enemy : m_Enemy)
	{
		enemy->draw(offset);
	}

	m_Particle->Draw(offset);
#ifdef _DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), "敵の数%d", m_Enemy.size());

	if (m_Player->GetNoDamageFrame() > 0)
	{
		DrawFormatString(0, 200, GetColor(255, 255, 255), "無敵時間%d", m_Player->GetNoDamageFrame());
	}
#endif
}

std::shared_ptr<EnemyBase> EnemyFactory::Create(EnemyType type, const Vec2 pos)
{
	switch (type) {
	case EnemyType::kNormal:
		m_Enemy.push_back(
			std::make_shared<Enemy1>()
		);
		break;
	case EnemyType::kFly:
		m_Enemy.push_back(
			std::make_shared<Enemy2>()
		);
		break;

	case EnemyType::kThrow:
		m_Enemy.push_back(
			std::make_shared<Enemy3>()
		);
		break;
	case EnemyType::kJump:
		m_Enemy.push_back(
			std::make_shared<Enemy4>()
		);
		break;
	case EnemyType::kFlyShot:
		m_Enemy.push_back(
			std::make_shared<Enemy5>()
		);
		break;
	case EnemyType::kKnight:
		m_Enemy.push_back(
			std::make_shared<Enemy6>()
		);
		break;
	case EnemyType::kBoss:
		m_Enemy.push_back(
			std::make_shared<BossEnemy>()
		);
		break;
	case EnemyType::kBoss2:
		m_Enemy.push_back(
			std::make_shared<BossEnemy2>()
		);
		break;
	}
	/*enemy* penemy = new enemy;
	penemy->setpos(pos);*/

	m_Enemy.back()->SetPos(pos);
	m_Enemy.back()->SetNextPos(pos);
	m_Enemy.back()->SetPlayer(m_Player);
	m_Enemy.back()->SetMap(m_Map);
	m_Enemy.back()->SetColl(m_Coll);
	m_Enemy.back()->SetHandle(m_handle);
	m_Enemy.back()->SetShotHandle(m_Shothandle);

	return m_Enemy.back();
}

void EnemyFactory::AttackDamage()
{
}

void EnemyFactory::StageEnemy(int StageNum)
{
	//if (StageNum == 0)
	//{
	//	//Create(kFlyShot, { 2000,500 });
	//	//Create(kBoss, { 2000,500 });
	//	/*Create(kFly, { 2000,800 });
	//	Create(kThrow, { 2000,800 });
	//	Create(kJump, { 2000,800 });
	//	Create(kFlyShot, { 2000,800 });
	//	Create(kFly, { 1000,800 });
	//	Create(kThrow, { 2000,800 });
	//	Create(kJump, { 1900,600 });
	//	Create(kJump, { 1900,300 });
	//	Create(kJump, { 3000,600 });
	//	Create(kJump, { 3500,600 });
	//	Create(kJump, { 5000,600 });
	//	Create(kFlyShot, { 1000,800 });
	//	Create(kFlyShot, { 7000,800 });
	//	Create(kFlyShot, { 4000,800 });
	//	Create(kJump, { 6000,600 });*/
	//	Create(kJump, { 6000,200 });
	//	Create(kJump, { 4000,600 });
	//	Create(kThrow, { 2050,400 });
	//	Create(kThrow, { 5500,800 });
	//	Create(kThrow, { 5300,800 });
	//	Create(kNormal, { 3000,800 });
	//	Create(kNormal, { 1600,600 });
	//	Create(kNormal, { 4000,800 });
	//	Create(kNormal, { 5000,600 });
	//	Create(kNormal, { 5500,800 });
	//	Create(kNormal, { 6000,800 });
	//	Create(kNormal, { 6500,600 });
	//}
	//
	//if (StageNum == 1)
	//{
	//	Create(kJump, { 1000,400 });
	//	/*Create(kJump, { 1100,300 });
	//	Create(kJump, { 1200,600 });
	//	Create(kJump, { 1300,600 });
	//	Create(kJump, { 1700,600 });
	//	Create(kJump, { 1800,200 });
	//	Create(kJump, { 1900,300 });
	//	Create(kJump, { 1400,600 });*/
	//	Create(kJump, { 1500,600 });
	//	Create(kJump, { 1600,400 });
	//	Create(kJump, { 2000,600 });
	//	Create(kJump, { 3500,600 });
	//	Create(kJump, { 5000,600 });
	//	Create(kJump, { 5500,600 });
	//	Create(kJump, { 5500,400 });
	//	Create(kJump, { 6000,600 });
	//	Create(kJump, { 6000,200 });
	//	Create(kJump, { 1900,300 });
	//	Create(kJump, { 3000,600 });
	//	Create(kJump, { 3500,600 });
	//	Create(kJump, { 5000,600 });
	//	Create(kJump, { 5500,600 });
	//	Create(kJump, { 5500,400 });
	//	Create(kJump, { 6000,600 });
	//	Create(kJump, { 6000,200 });
	//}

	//if (StageNum == 2)
	//{
	//	Create(kThrow, { 1000,400 });
	//	Create(kThrow, { 1100,300 });
	//	Create(kThrow, { 1200,600 });
	//	Create(kThrow, { 1300,600 });
	//	Create(kThrow, { 1400,600 });
	//	Create(kThrow, { 1500,600 });
	//	Create(kThrow, { 1600,400 });
	//	Create(kThrow, { 1700,600 });
	//	Create(kThrow, { 1800,200 });
	//	Create(kThrow, { 1900,300 });
	//	Create(kThrow, { 2000,600 });
	//	Create(kThrow, { 3500,600 });
	//	Create(kThrow, { 5000,600 });
	//	Create(kThrow, { 5500,600 });
	//	Create(kThrow, { 5500,400 });
	//	Create(kThrow, { 6000,600 });
	//	Create(kThrow, { 6000,200 });
	//	Create(kThrow, { 1900,300 });
	//	Create(kThrow, { 3000,600 });
	//	Create(kThrow, { 3500,600 });
	//	Create(kThrow, { 5000,600 });
	//	Create(kThrow, { 5500,600 });
	//	Create(kThrow, { 5500,400 });
	//	Create(kThrow, { 6000,600 });
	//	Create(kThrow, { 6000,200 });
	//}

	//if (StageNum == 3)
	//{
	//	Create(kJump, { 1000,400 });
	//	Create(kJump, { 1100,300 });
	//	Create(kJump, { 1200,600 });
	//	Create(kJump, { 1300,600 });
	//	Create(kJump, { 1400,600 });
	//	Create(kJump, { 1500,600 });
	//	Create(kJump, { 1600,400 });
	//	Create(kJump, { 1700,600 });
	//	Create(kJump, { 1800,200 });
	//	Create(kJump, { 1900,300 });
	//	Create(kJump, { 2000,600 });
	//	Create(kJump, { 3500,600 });
	//	Create(kJump, { 5000,600 });
	//	Create(kJump, { 5500,600 });
	//	Create(kJump, { 5500,400 });
	//	Create(kJump, { 6000,600 });
	//	Create(kJump, { 6000,200 });
	//	Create(kJump, { 1900,300 });
	//	Create(kJump, { 3000,600 });
	//	Create(kJump, { 3500,600 });
	//	Create(kJump, { 5000,600 });
	//	Create(kJump, { 5500,600 });
	//	Create(kJump, { 5500,400 });
	//	Create(kJump, { 6000,600 });
	//	Create(kJump, { 6000,200 });
	//}

	//if (StageNum == 4)
	//{
	//	Create(kJump, { 1000,400 });
	//	Create(kJump, { 1100,300 });
	//	Create(kJump, { 1200,600 });
	//	Create(kJump, { 1300,600 });
	//	Create(kJump, { 1400,600 });
	//	Create(kJump, { 1500,600 });
	//	Create(kJump, { 1600,400 });
	//	Create(kJump, { 1700,600 });
	//	Create(kJump, { 1800,200 });
	//	Create(kJump, { 1900,300 });
	//	Create(kJump, { 2000,600 });
	//	Create(kJump, { 3500,600 });
	//	Create(kJump, { 5000,600 });
	//	Create(kJump, { 5500,600 });
	//	Create(kJump, { 5500,400 });
	//	Create(kJump, { 6000,600 });
	//	Create(kJump, { 6000,200 });
	//	Create(kJump, { 1900,300 });
	//	Create(kJump, { 3000,600 });
	//	Create(kJump, { 3500,600 });
	//	Create(kJump, { 5000,600 });
	//	Create(kJump, { 5500,600 });
	//	Create(kJump, { 5500,400 });
	//	Create(kJump, { 6000,600 });
	//	Create(kJump, { 6000,200 });
	//}

	for (int i = 0; i < Map::kBgNumY[m_Map->GetStageNum()]; i++)
	{
		for (int j = 0; j < Map::kBgNumX[m_Map->GetStageNum()]; j++)
		{
			Vec2 Pos = { j * Map::kChipSize,i * Map::kChipSize };

			if (m_Map->GetMapData(i, j) == 240)
			{
				Create(kNormal, { Pos });
			}
			if (m_Map->GetMapData(i, j) == 241)
			{
				Create(kFly, { Pos });
			}
			if (m_Map->GetMapData(i, j) == 242)
			{
				Pos.y -= 30;
				Create(kThrow, { Pos });
			}
			if (m_Map->GetMapData(i, j) == 243)
			{
				Create(kJump, { Pos });
			}
			if (m_Map->GetMapData(i, j) == 244)
			{
				Create(kFlyShot, { Pos });
			}
			if (m_Map->GetMapData(i, j) == 224)
			{
				Pos.y -= 200;
				Create(kKnight, { Pos });
			}
			if (m_Map->GetMapData(i, j) == 245)
			{
				Pos.y -= 400;
				Create(kBoss, { Pos });
			}
			if (m_Map->GetMapData(i, j) == 225)
			{
				Pos.y -= 400;
				Create(kBoss2, { Pos });
			}
		}
	}
}

void EnemyFactory::EnemyDead()
{
	//実際に範囲を指定して消す
	m_Enemy.erase(m_Enemy.begin(), m_Enemy.end());
}

bool EnemyFactory::GetAttackTutorialFlag()
{
	for (auto& enemy : m_Enemy)
	{
		if(enemy->GetTutorialFlag())
		{
			return true;
		}
	}

	return false;
}

bool EnemyFactory::GetBossBattle()
{
	for (auto& enemy : m_Enemy)
	{
		if (enemy->GetBossBattle())
		{
			return true;
		}
	}

	return false;
}

bool EnemyFactory::GetGameClear()
{
	for (auto& enemy : m_Enemy)
	{
		if (enemy->GetGameClear())
		{
			return true;
		}
	}

	return false;
}
