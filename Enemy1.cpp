#include "Enemy1.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Map.h"
#include <Dxlib.h>
#include <cassert>

namespace
{
	// d—Í
	constexpr float kGravity = 0.05f;
}

Enemy1::Enemy1() 
{
	m_func = &Enemy1::UpdatePatrol;
}

Enemy1::~Enemy1()
{
}

void Enemy1::update()
{
	m_PlayerPos = m_Player->GetPos();
	(this->*m_func)();

	m_DistancePos = m_Pos - m_PlayerPos;

	if (m_DistancePos.x > -500 && m_DistancePos.x < 500)
	{
		m_func = &Enemy1::UpdateDiscovery;
	}

	if (m_Pos.y > Game::kScreenHeight)
	{
		m_isDead = true;
	}
}

void Enemy1::UpdatePatrol()
{
	MoveEnemy();
}

void Enemy1::UpdateDiscovery()
{
	
}

void Enemy1::updateAttack()
{
}

