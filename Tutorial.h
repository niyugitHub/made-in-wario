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
		kDamageFlag,
	};
public:
	Tutorial();
	~Tutorial();

	bool GetJumpFlag() { return m_JumpFlag; }
	bool GetAttackFlag() { return m_AttackFlag; }
	bool GetDashFlag() { return m_DashFlag; }
	bool GetTwoJumpFlag() { return m_TwoJumpFlag; }
	bool GetShotFlag() { return m_ShotFlag; }
	bool GetDamageFlag() { return m_DamageFlag; }

	void SetAttackUpFlag(bool AttackUpFlag) { m_AttackUpFlag = AttackUpFlag; }
	bool GetAttackUpFlag() { return m_AttackUpFlag; }

	void SetHpUpFlag(bool HpUpFlag) { m_HpUpFlag = HpUpFlag; }
	bool GetHpUpFlag() { return m_HpUpFlag; }

	void SetGaugeUpFlag(bool GaugeUpFlag) { m_GaugeUpFlag = GaugeUpFlag; }
	bool GetGaugeUpFlag() { return m_GaugeUpFlag; }

	void SetPastJumpFlag(bool PastJumpFlag) { m_PastJumpFlag = PastJumpFlag; }
	bool GetPastJumpFlag() { return m_PastJumpFlag; }

	void SetPastAttackFlag(bool PastAttackFlag) { m_PastAttackFlag = PastAttackFlag; }
	bool GetPastAttackFlag() { return m_PastAttackFlag; }

	void SetPastDashFlag(bool PastDashFlag) { m_PastDashFlag = PastDashFlag; }
	bool GetPastDashFlag() { return m_PastDashFlag; }

	bool GetPastTwoJumpFlag() { return m_PastTwoJumpFlag; }
	bool GetPastShotFlag() { return m_PastShotFlag; }
	bool GetPastDamageFlag() { return m_PastDamageFlag; }

	void SetPastAttackUpFlag(bool PastAttackUpFlag) { m_PastAttackUpFlag = PastAttackUpFlag; }
	bool GetPastAttackUpFlag() { return m_PastAttackUpFlag; }

	void SetPastHpUpFlag(bool PastHpUpFlag) { m_PastHpUpFlag = PastHpUpFlag; }
	bool GetPastHpUpFlag() { return m_PastHpUpFlag; }

	void SetPastGaugeUpFlag(bool PastGaugeUpFlag) { m_PastGaugeUpFlag = PastGaugeUpFlag; }
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
	bool m_DamageFlag = false;

	bool m_PastJumpFlag = false;
	bool m_PastAttackFlag = false;
	bool m_PastDashFlag = false;
	bool m_PastTwoJumpFlag = false;
	bool m_PastShotFlag = false;
	bool m_PastAttackUpFlag = false;
	bool m_PastHpUpFlag = false;
	bool m_PastGaugeUpFlag = false;
	bool m_PastDamageFlag = false;

	/*int m_PlayerHandle = -1;
	int m_OptionHandle = -1;*/

	int m_Count = 0;
};

