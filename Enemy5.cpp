#include "Enemy5.h"
#include "EnemyBase.h"

Enemy5::Enemy5()
{
	m_Hp = 30;
	m_func = &Enemy5::UpdatePatrol;
}

Enemy5::~Enemy5()
{
}

void Enemy5::update()
{
}

void Enemy5::UpdatePatrol()
{
}

void Enemy5::UpdateDiscovery()
{
}

void Enemy5::updateAttack()
{
}
