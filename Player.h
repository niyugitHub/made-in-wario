#pragma once
#include "Vec2.h"
#include<memory>

class Map;
class SceneTitle;
class PlayerShot;

class Player 
{
public:
	// �v���C���[�̏����ʒu
	static constexpr float kFristPlayerPosX = 760.0f;
	static constexpr float kFristPlayerPosY = 500.0f;

	static constexpr int kSideSize = 128;
	static constexpr int kColumnSize = 128;

	static constexpr int kSideCharaChipNum = 8;
	static constexpr int kColumnCharaChipNum = 9;

	static constexpr int kCharaChipNum = kSideCharaChipNum * kColumnCharaChipNum;

	// �m�b�N�o�b�N(�U�����󂯂��Ƃ�)�̃X�s�[�h
	static constexpr float kKnockBackSpeed = 12.0f;
	// �m�b�N�o�b�N(�U���𓖂Ă��Ƃ�)�̃X�s�[�h
	static constexpr float kHitKnockBackSpeed = 6.0f;
public:
	Player();
	virtual ~Player();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	void setMap(std::shared_ptr<Map> pMap) { m_Map = pMap; }
	void SetTitle(SceneTitle* pTitle) { m_SceneTitle = pTitle; }

	void SetPos(Vec2 pos) { m_pos = pos; }

	void SetCollTop(bool Top) { m_CollTop = Top; }
	void SetCollBottom(bool Bottom) { m_CollBottom = Bottom; }
	void SetCollRight(bool Right) { m_CollRight = Right; }
	void SetCollLeft(bool Left) { m_CollLeft = Left; }

	void SetCollItemTwoJump(bool TwoJump) { m_PossibleTwoJump = TwoJump; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }

	Vec2 GetPos() const { return m_pos; }

	Vec2 GetNextPos()const { return m_NextPos; }

	//�V���b�g�̍��W
	void SetShotPos(Vec2 ShotPos) { m_ShotPos = ShotPos; }
	Vec2 GetShotPos() { return m_ShotPos; }

	void SetAttackPower(int AttackPower) { m_AttackPower = AttackPower; }
	int GetAttackPower() { return m_AttackPower; }

	float GetMove() const { return m_StartMove; }

	// �v���C���[�̍U������ƌ�����Ԃ�
	bool GetAttack() { return m_Attack; }
	bool GetLook() { return m_LookLeft; }

	//// �U���q�b�g�m�F ����m_HitAttack��true�̏ꍇ�G�ɍU����������Ȃ�(�A���œG�Ƀq�b�g����̂�h������)
	//void SetHitAttack(bool HitAttack) { m_HitAttack = HitAttack; }
	bool GetInitAttack() { return m_InitAttack; }

	// ���G����
	void SetNoDamageFrame(int NoDamage) { m_NoDamageFrame = NoDamage; }
	int GetNoDamageFrame() { return m_NoDamageFrame; }

	// �G���W�擾
	void SetEnemyPos(Vec2 EnemyPos) { m_EnemyPos = EnemyPos; };

	// �m�b�N�o�b�N�X�s�[�h�擾
	void SetKnockBackSpeed(float KnockbackSpeed){m_KnockBack = KnockbackSpeed;}

	void Init();
	void end();

	void update();
	void draw(Vec2 offset);

	// �L�����̓��������߂�
	void CharaMove();

	// �L�����̃W�����v����
	void CharaJump();

	// �����̐���
	void LimitMove();

	// �v���C���[�����񂾂Ƃ��̏���
	void NotExist();

	// �v���C���[�̓������߂̏���
	void IsMoveStart();

	// �v���C���[���~�܂����Ƃ��̏���
	void IsMoveStop();

	//// �G�̍U��������������
	void Ondamage();

	// �m�b�N�o�b�N����
	void IsKnockBack(Vec2 EnemyPos);

	// �񕜏���
	void IsActiveGauge();

	// �Q�[�W
	void IsGauge();

	// �����蔻��
	void IsColl();

	// �V���b�g�̓����蔻��
	bool IsShotColl();
	
	//�����蔻�菉����
	void InitColl();

	//�{�^�������Ă邩�m�F
	bool PushButton();

	// �v���C���[�������������ǂ���
	bool FallPlayer();

	// �O���t�B�b�N�f�[�^�ݒ�
//	void setHandle(int index, int handle) { m_handle[index] = handle; }

private:
	// ���݂̍��W
	Vec2 m_pos;
	// ���t���[�����̍��W
	Vec2 m_NextPos;

	Vec2 m_vec;

	// �G���W�擾
	Vec2 m_EnemyPos;

	// �V���b�g�̍��W�擾
	Vec2 m_ShotPos;

	float m_StartMove;

	float m_Jump;

	// �O���t�̑}��
	int m_handle[kCharaChipNum];

	// �L�����N�^�[�̃O���t�̎�ނ����߂�
	int m_CharaGraphX;
	int m_CharaGraphY;

	// ���Ԃɂ���ăL�����̓�����ς���
	int m_FrameChangeChara;

	// �L�����̓�����ς��鑬�x
	int m_FrameChangeSpeed;

	// �e���[�V�����̃L�����̓����̐�
	int m_CharaMotion;

	// �L�����N�^�[�̏d��
	float m_Gravity;

	// �L�����N�^�[�������Ă��邩�ǂ���
	bool m_NowDash;

	// �L�����N�^�[�����������Ă��邩�ǂ���
	bool m_LookLeft;

	// �L�����N�^�[���W�����v�����Ă���Ƃ�
	bool m_NowJump;

	// �L�����N�^�[����i�W�����v���Ă���Ƃ�
	bool m_TwoJump;

	// �L�����N�^�[����i�W�����v���g�����Ƃ�
	bool m_UseTwoJump;

	// �L�����N�^�[���n�ʂɂ��Ă��邩�ǂ���
	bool m_Coll_Ground;

	// �L�����N�^�[�ƃu���b�N�̏Փ˔���
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	// �v���C���[�ƃA�C�e�����G�ꂽ�Ƃ�(��i�W�����v)
	bool m_PossibleTwoJump;

	// �L�����N�^�[���U���������Ƃ�
	bool m_Attack;

	// �U�����q�b�g�����Ƃ�
	bool m_InitAttack;

	// �v���C���[�̍U���́@
	int m_AttackPower;

	// �v���C���[�̗̑�
	int m_Hp;
	// �v���C���[�̍ő�̗�
	int m_MaxHp;

	// �v���C���[�̖��G����
	int m_NoDamageFrame;

	// �m�b�N�o�b�N�X�s�[�h
	float m_KnockBack;

	// �{�^��������������
	int m_PushFrame;

	// �Q�[�W��
	int m_Gauge;

	// �V���b�g��łĂ邩�ǂ���
	bool m_PossibleShot;
	// �V���b�g��ł������ǂ���
//	bool m_Shot;

	// �L�����N�^�[�̑��݊m�F
	bool m_Exist;
	
	std::shared_ptr<Map> m_Map;
	SceneTitle* m_SceneTitle;
	PlayerShot* m_Shot;
};

