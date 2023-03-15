#include "GimmickBase.h"
#include<DxLib.h>

GimmickBase::GimmickBase() : 
	m_Pos(0,0),
	m_handle(-1),
	m_GraphX(0),
	m_GraphY(0),
	m_offset(0,0),
	m_GraphSize1(0,0),
	m_GraphSize2(0, 0),
	m_Flag(false)
{
}

GimmickBase::~GimmickBase()
{
}

void GimmickBase::Init()
{
}

void GimmickBase::Update(Vec2 PlayerPos)
{
}

void GimmickBase::Draw(Vec2 offset)
{
	/*DrawRectGraph(m_Pos.x + offset.x, m_Pos.y + offset.y,
		m_GraphX * m_GraphSize.x, m_GraphY, m_GraphSize.y,
		m_handle, true, true);*/
}
