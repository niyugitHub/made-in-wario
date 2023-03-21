#pragma once
#include "Vec2.h"
#include<memory>

class Map;
class SceneTitle;
class PlayerShot;
class Particle;

class Player 
{
public:
	// �v���C���[�̏����ʒu
	static constexpr float kFristPlayerPosX = 760.0f;
	static constexpr float kFristPlayerPosY = 800.0f;

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

	// �_���[�W���󂯂��t���O���Z�b�g
	void SetDamage(bool Damage) { m_Damage = Damage; }
	bool GetDamage() { return m_Damage; }

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

	// �X�e�[�W�N���A
	void SetStageClaer(bool StageClaer) { m_StageClear = StageClaer; }
	bool GetStageClaer() { return m_StageClear; }

	// �G���W�擾
	void SetEnemyPos(Vec2 EnemyPos) { m_EnemyPos = EnemyPos; };

	// �V���b�g�A�C�e�����擾�����Ƃ��V���b�g��łĂ�悤��
	void SetShot(bool PossibleShot) { m_PossibleShot = PossibleShot; }

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

	// MaxHp����
	void MaxHpUp();

	// MaxGauge����
	void MaxGaugeUp();

	// �M�~�b�N�ɓ��������Ƃ�
	void CollGimmick();

	// �g�Q�ɓ��������Ƃ�
	bool CollNeedle();
	// �T�E���h
	void IsSound();

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
	int m_Hphandle;
	int m_Gaugehandle;
	int m_Gauge1handle;
	int m_Shothandle;

	// ���n���h���̒ǉ�
	int m_SoundAttack = -1;
	int m_SoundJump = -1;
	int m_SoundWalk = -1;
	int m_SoundDash = -1;
	int m_SoundDamage = -1;
	int m_SoundHeal = -1;
	int m_SoundHealCompleted = -1;
	int m_SoundShot = -1;

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

	//Max�Q�[�W
	int m_MaxGauge;

	// �Q�[�W�̌���(�����ڂ��悭���邽�߂̕ϐ�)
	int m_MinusGauge = 0;

	// �V���b�g��łĂ邩�ǂ���
	bool m_PossibleShot;
	// �V���b�g�Ԋu
	int m_ShotIntervalFrame;
	// �V���b�g��ł������ǂ���
//	bool m_Shot;

	// �_���[�W��H������t���O
	bool m_Damage = false;

	// �X�e�[�W���N���A�����Ƃ�
	bool m_StageClear;

	// �L�����N�^�[�̑��݊m�F
	bool m_Exist;

	std::shared_ptr<Map> m_Map;
	SceneTitle* m_SceneTitle;
	PlayerShot* m_Shot;
	std::shared_ptr<Particle> m_Particle;
};

