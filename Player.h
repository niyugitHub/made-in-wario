#pragma once
#include "Vec2.h"

class SceneTitle;

class Collision;

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
public:
	Player();
	virtual ~Player();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	void SetTitle(SceneTitle* pTitle) { m_SceneTitle = pTitle; }

	void SetPos(Vec2 pos) { m_pos = pos; }

	void SetCollTop(bool Top) { m_CollTop = Top; }
	void SetCollBottom(bool Bottom) { m_CollBottom = Bottom; }
	void SetCollRight(bool Right) { m_CollRight = Right; }
	void SetCollLeft(bool Left) { m_CollLeft = Left; }

	void SetCollItemTwoJump(bool TwoJump) { m_PossibleTwoJump = TwoJump; }

	void SetExist(bool Exist) { m_Exist = Exist; }

	Vec2 GetPos() const { return m_pos; }

	void SetAttackPower(int AttackPower) { m_AttackPower = AttackPower; }
	int GetAttackPower() { return m_AttackPower; }

	int GetMove() const { return m_StartMove; }

	// �v���C���[�̍U������ƌ�����Ԃ�
	bool GetAttack() { return m_Attack; }
	bool GetLook() { return m_LookLeft; }

	void Init();
	void end();

	void update();
	void draw();

	// �L�����̓��������߂�
	void CharaMove();

	// �L�����̃W�����v����
	void CharaJump();

	// �����̐���
	void LimitMove();

	// �v���C���[�����񂾂Ƃ��̏���
	void NotExist();

	// �v���C���[�̓������߂̏���
	void IsMoveStartLeft();

	// �v���C���[�̓������߂̏���
	void IsMoveStartRight();

	// �v���C���[���~�܂����Ƃ��̏���
	void IsMoveStop();

	// �O���t�B�b�N�f�[�^�ݒ�
//	void setHandle(int index, int handle) { m_handle[index] = handle; }

private:
	Vec2 m_pos;
	Vec2 m_vec;

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

	// �������J�n�����Ƃ��̃t���O
	bool m_IsMove;

	// �v���C���[�̍U���́@
	int m_AttackPower;

	// �v���C���[�̗̑�
	int m_Hp;

	// �L�����N�^�[�̑��݊m�F
	bool m_Exist;

	SceneTitle* m_SceneTitle;
};

