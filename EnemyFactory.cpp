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
	//いなくなった敵は消えてもらう
	//消す命令のくせに、実際には決してなくて、後ろによけてるだけ
	auto rmIt = std::remove_if(//条件に合致したものを消す
		m_Enemy.begin(),	//対象はm_Enemyの最初から
		m_Enemy.end(),		//最後まで
		//消えてもらう条件を表すラムダ式
		//trueだと消える。falseだと消えない
		[](const std::shared_ptr<EnemyBase>& enemy) {
			return !enemy->isExist();
		});

	//実際に範囲を指定して消す
	m_Enemy.erase(rmIt, m_Enemy.end());
	//ここまでやらないと実際には消えないので注意
	
	for (auto& enemy : m_Enemy)
	{
		if (enemy->isExist())
		{
			enemy->update();

			m_Coll->Update();

			// エネミーとマップの当たり判定
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
	
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "敵の数%d", m_Enemy.size());
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
