#include "EnemyFactory.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "EnemyBase.h"

EnemyFactory::EnemyFactory() : 
	m_EnemyName(kNormal)
{
	
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
	
}

void EnemyFactory::Draw()
{
	
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

	return m_Enemy.back();
}
