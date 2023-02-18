#include "ShotBase.h"
#include "game.h"
#include <Dxlib.h>

ShotBase::ShotBase() : 
	m_Pos(0,0),
	m_Vec(0,0),
	m_Exist(true)
{
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update()
{
}

void ShotBase::Draw(Vec2 offset)
{
}
