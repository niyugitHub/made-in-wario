#include "Collision.h"
#include "EnemyFactory.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "EnemyBase.h"
#include "Player.h"
#include <DxLib.h>
#include <cassert>

EnemyFactory::EnemyFactory() : 
	m_EnemyName(kNormal),
	m_Frame(0),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollRight(false),
	m_CollLeft(false),
	m_Pos(0,0)
{
//	m_Coll = std::make_shared<Collision>();
}

EnemyFactory::~EnemyFactory()
{
}

void EnemyFactory::Init()
{
	
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

	Stage1Enemy();
	//���Ȃ��Ȃ����G�͏����Ă��炤
	//�������߂̂����ɁA���ۂɂ͌����ĂȂ��āA���ɂ悯�Ă邾��
	auto rmIt = std::remove_if(//�����ɍ��v�������̂�����
		m_Enemy.begin(),	//�Ώۂ�m_Enemy�̍ŏ�����
		m_Enemy.end(),		//�Ō�܂�
		//�����Ă��炤������\�������_��
		//true���Ə�����Bfalse���Ə����Ȃ�
		[](const std::shared_ptr<EnemyBase>& enemy) {
			return !enemy->isExist();
		});

	//���ۂɔ͈͂��w�肵�ď���
	m_Enemy.erase(rmIt, m_Enemy.end());
	//�����܂ł��Ȃ��Ǝ��ۂɂ͏����Ȃ��̂Œ���

	for (auto& enemy : m_Enemy)
	{
		if (!m_Player->GetHitAttack())
		{
			enemy->SetHit(false);
		}
	}
	
	for (auto& enemy : m_Enemy)
	{
		if (enemy->isExist())
		{
			m_Coll->InitColl();

			enemy->update();
			
			/*enemy->update();*/

			m_Pos = enemy->GetPos();

			m_Coll->Update();

			if (m_Coll->IsCollEnemy() && m_Player->GetNoDamageFrame() <= 0)
			{
				DrawString(500, 0, "����", GetColor(100, 255, 100));
				m_Player->Ondamage();
				m_Player->SetNoDamageFrame(100);
				m_Player->SetEnemyPos(m_Pos);
			}

			// �G�l�~�[�ƃ}�b�v�̓����蔻��
			m_CollTop = m_Coll->IsCollTopEnemy();
			m_CollBottom = m_Coll->IsCollBottomEnemy();
			m_CollRight = m_Coll->IsCollRightEnemy();
			m_CollLeft = m_Coll->IsCollLeftEnemy();

			enemy->SetCollTop(m_CollTop);
			enemy->SetCollBottom(m_CollBottom);
			enemy->SetCollRight(m_CollRight);
			enemy->SetCollLeft(m_CollLeft);

			enemy->SetPos(m_Pos);

			if (m_Coll->IsCollAttackPlayer() && !enemy->GetHit())
			{
				m_Player->SetHitAttack(true);
				enemy->SetHit(true);
				enemy->OnDamage(m_Player->GetAttackPower());
				enemy->InitKnockBack();
			}

			if (enemy->GetHit())
			{
				enemy->KnockBack();
			}
		}
	}
}

void EnemyFactory::Draw()
{
	for (auto& enemy : m_Enemy)
	{
		if (enemy->isExist())
		{
			enemy->draw();
		}
	}
#ifdef _DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�G�̐�%d", m_Enemy.size());

	if (m_Player->GetNoDamageFrame() > 0)
	{
		DrawFormatString(0, 200, GetColor(255, 255, 255), "���G����%d", m_Player->GetNoDamageFrame());
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
	case EnemyType::kJump:
		m_Enemy.push_back(
			std::make_shared<Enemy2>()
		);
		break;
	}
	/*enemy* penemy = new enemy;
	penemy->setpos(pos);*/

	m_Enemy.back()->SetPos(pos);
	m_Enemy.back()->SetPlayer(m_Player);
	m_Enemy.back()->SetMap(m_Map);
	m_Enemy.back()->SetColl(m_Coll);

	return m_Enemy.back();
}

void EnemyFactory::AttackDamage()
{
}

void EnemyFactory::Stage1Enemy()
{
	m_Frame++;

	if (m_Frame == 1)
	{
		Create(kJump, { 300,600 });
		Create(kJump, { 1500,600 });
		Create(kJump, { 1500,600 });
		Create(kJump, { 1600,600 });
		Create(kJump, { 1700,600 });
		Create(kJump, { 1800,600 });
		Create(kJump, { 1900,600 });
		Create(kJump, { 2000,600 });
		Create(kJump, { 300,600 });
		Create(kJump, { 3000,600 });
		Create(kJump, { 3500,600 });
		Create(kJump, { 4000,600 });
		Create(kJump, { 1500,600 });
		Create(kNormal, { 1000,600 });
		Create(kNormal, { 3000,800 });
		Create(kNormal, { 4000,800 });
		Create(kNormal, { 5000,600 });
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });

	}

	/*if (m_Frame == 2)
	{
		Create(kJump, { 1800,600 });
		Create(kJump, { 1900,600 });
	}

	if (m_Frame == 3)
	{
		Create(kJump, { 2000,600 });
		Create(kJump, { 300,600 });
	}

	if (m_Frame == 4)
	{
		Create(kJump, { 3000,600 });
		Create(kJump, { 3500,600 });
	}

	if (m_Frame == 5)
	{
		Create(kJump, { 4000,600 });
		Create(kJump, { 1500,600 });
	}

	if (m_Frame == 6)
	{
		Create(kNormal, { 1000,600 });
		Create(kNormal, { 3000,800 });
	}

	if (m_Frame == 7)
	{
		Create(kNormal, { 4000,800 });
		Create(kNormal, { 5000,600 });
	}

	if (m_Frame == 8)
	{
		Create(kNormal, { 1500,600 });
		Create(kNormal, { 1500,600 });
	}*/
}
