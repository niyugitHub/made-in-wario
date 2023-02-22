#include "Enemy4.h"
#include "EnemyBase.h"

Enemy4::Enemy4()
{
	m_Hp = 30;
	m_func = &Enemy4::UpdatePatrol;
}

Enemy4::~Enemy4()
{
}

void Enemy4::update()
{
}

void Enemy4::UpdatePatrol()
{
}

void Enemy4::UpdateDiscovery()
{
}

void Enemy4::updateAttack()
{
}
