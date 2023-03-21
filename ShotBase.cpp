#include "ShotBase.h"
#include "game.h"
#include <Dxlib.h>

ShotBase::ShotBase() : 
	m_Pos(0,0),
	m_Vec(0,0),
	m_ShotSize1(0,0),
	m_ShotSize2(50,50),
	m_Exist(false),
	m_handle(-1),
	m_GraphX(0),
	m_GraphY(0),
	m_Frame(0)
{
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update(Vec2 PlayerPos)
{
}

void ShotBase::Draw(Vec2 offset)
{
}
