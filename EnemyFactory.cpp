#include "Collision.h"
#include "EnemyFactory.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "EnemyBase.h"
#include <DxLib.h>
#include <cassert>

EnemyFactory::EnemyFactory() : 
	m_EnemyName(kNormal),
	m_Frame(0),
	m_CollTop(false),
	m_CollBottom(false),
	m_CollRight(false),
	m_CollLeft(false)
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
	m_Frame++;

	if (m_Frame % 60 == 0)
	{
		Create(kNormal, { 1500,600 });
	}
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
		if (enemy->isExist())
		{
			enemy->update();

			m_Coll->Update();

			// �G�l�~�[�ƃ}�b�v�̓����蔻��
			m_CollTop = m_Coll->IsCollTopEnemy();
			m_CollBottom = m_Coll->IsCollBottomEnemy();
			m_CollRight = m_Coll->IsCollRightEnemy();
			m_CollLeft = m_Coll->IsCollLeftEnemy();

			enemy->SetCollTop(m_CollTop);
			enemy->SetCollBottom(m_CollBottom);
			enemy->SetCollRight(m_CollRight);
			enemy->SetCollLeft(m_CollLeft);

			//assert(!m_CollBottom);

			if (m_Coll->IsCollAttackPlayer())
			{
				enemy->setExist(false);
			}

			m_Coll->InitColl();
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
	
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "�G�̐�%d", m_Enemy.size());
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
