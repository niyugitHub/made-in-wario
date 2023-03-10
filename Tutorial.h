#pragma once
class Tutorial
{
public:
	enum FlagCategory
	{
		kJumpFlag,
		kAttackFlag,
		kDashFlag,
		kTwoJumpFlag,
		kShotFlag,
		kAttackUpFlag,
		kHpUpFlag,
		kGaugeUpFlag,
	};
public:
	Tutorial();
	~Tutorial();

	bool GetJumpFlag() { return m_JumpFlag; }
	bool GetAttackFlag() { return m_AttackFlag; }
	bool GetDashFlag() { return m_DashFlag; }
	bool GetTwoJumpFlag() { return m_TwoJumpFlag; }
	bool GetShotFlag() { return m_ShotFlag; }
	bool GetAttackUpFlag() { return m_AttackUpFlag; }
	bool GetHpUpFlag() { return m_HpUpFlag; }
	bool GetGaugeUpFlag() { return m_GaugeUpFlag; }

	bool GetPastJumpFlag() { return m_PastJumpFlag; }
	bool GetPastAttackFlag() { return m_PastAttackFlag; }
	bool GetPastDashJFlag() { return m_PastDashFlag; }
	bool GetPastTwoJumpFlag() { return m_PastTwoJumpFlag; }
	bool GetPastShotFlag() { return m_PastShotFlag; }
	bool GetPastAttackUpFlag() { return m_PastAttackUpFlag; }
	bool GetPastHpUpFlag() { return m_PastHpUpFlag; }
	bool GetPastGaugeUpFlag() { return m_PastGaugeUpFlag; }

	void Init();

	void SetFlag(bool Flag, int Type);
	
	void Update();
	void Draw();

private:
	bool m_JumpFlag = false;
	bool m_AttackFlag = false;
	bool m_DashFlag = false;
	bool m_TwoJumpFlag = false;
	bool m_ShotFlag = false;
	bool m_AttackUpFlag = false;
	bool m_HpUpFlag = false;
	bool m_GaugeUpFlag = false;

	bool m_PastJumpFlag = false;
	bool m_PastAttackFlag = false;
	bool m_PastDashFlag = false;
	bool m_PastTwoJumpFlag = false;
	bool m_PastShotFlag = false;
	bool m_PastAttackUpFlag = false;
	bool m_PastHpUpFlag = false;
	bool m_PastGaugeUpFlag = false;

	/*int m_PlayerHandle = -1;
	int m_OptionHandle = -1;*/

	int m_Count = 0;
};

