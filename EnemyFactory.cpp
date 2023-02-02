#include "EnemyFactory.h"
#include "Enemy1.h"
#include "Enemy2.h"

EnemyFactory::EnemyFactory() : 
	m_EnemyName(kNormal),
	m_NormalEnemy(nullptr),
	m_JumpEnemy(nullptr)
{
}

EnemyFactory::~EnemyFactory()
{
}

void EnemyFactory::Init()
{
	switch (m_EnemyName)
	{
	case kNormal:
		m_NormalEnemy = new Enemy1;
		break;

	case kJump:
		m_JumpEnemy = new Enemy2;
		break;
	}
}

void EnemyFactory::end()
{
}

void EnemyFactory::Update()
{
	switch (m_EnemyName)
	{
	case kNormal:
		m_NormalEnemy->update();
		break;

	case kJump:
		m_JumpEnemy->update();
		break;
	}
}

void EnemyFactory::Draw()
{
	switch (m_EnemyName)
	{
	case kNormal:
		m_NormalEnemy->draw();
		break;

	case kJump:
		m_JumpEnemy->draw();
		break;
	}
}
