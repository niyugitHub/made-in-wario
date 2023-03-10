#include "Tutorial.h"
#include"Pad.h"
#include <DxLib.h>
Tutorial::Tutorial()
{
}

Tutorial::~Tutorial()
{
}

void Tutorial::Init()
{
}

void Tutorial::SetFlag(bool Flag, int Type)
{
	if (Type == kJumpFlag)
	{
		m_JumpFlag = Flag;
	}
	if (Type == kAttackFlag)
	{
		m_AttackFlag = Flag;
	}
	if (Type == kDashFlag)
	{
		m_DashFlag = Flag;
	}
	if (Type == kTwoJumpFlag)
	{
		m_TwoJumpFlag = Flag;
	}
	if (Type == kShotFlag)
	{
		m_ShotFlag = Flag;
	}
	if (Type == kAttackUpFlag)
	{
		m_AttackUpFlag = Flag;
	}
	if (Type == kHpUpFlag)
	{
		m_HpUpFlag = Flag;
	}
	if (Type == kGaugeUpFlag)
	{
		m_GaugeUpFlag = Flag;
	}

	m_Count = 0;
}

void Tutorial::Update()
{
	m_Count++;
	if (Pad::isTrigger(PAD_INPUT_2) && m_JumpFlag && m_Count >= 25)
	{
		m_PastJumpFlag = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_AttackFlag && m_Count >= 25)
	{
		m_PastAttackFlag = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_DashFlag && m_Count >= 25)
	{
		m_PastDashFlag = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_TwoJumpFlag && m_Count >= 25)
	{
		m_PastTwoJumpFlag = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_ShotFlag && m_Count >= 25)
	{
		m_PastShotFlag = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_AttackUpFlag && m_Count >= 25)
	{
		m_PastAttackUpFlag = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_HpUpFlag && m_Count >= 25)
	{
		m_PastHpUpFlag = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_GaugeUpFlag && m_Count >= 25)
	{
		m_PastGaugeUpFlag = true;
	}
}

void Tutorial::Draw()
{
	if (m_JumpFlag)
	{
		
	}

	if (m_AttackFlag)
	{
		
	}

	if (m_DashFlag)
	{
		
	}

	if (m_TwoJumpFlag)
	{
		
	}

	if (m_ShotFlag)
	{
		
	}

	if (m_AttackUpFlag)
	{
		
	}

	if (m_HpUpFlag)
	{
		
	}

	if (m_GaugeUpFlag)
	{
		
	}
}
