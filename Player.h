#pragma once
#include "Vec2.h"

class SceneTitle;

class Player 
{
public:
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

	Vec2 GetPos() const { return m_pos; }

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

	// �O���t�B�b�N�f�[�^�ݒ�
//	void setHandle(int index, int handle) { m_handle[index] = handle; }

private:
	Vec2 m_pos;
	Vec2 m_vec;

	float m_Jump;

	// �O���t�̑}��
	int m_handle[kCharaChipNum];

	// �L�����N�^�[�̃O���t�̎�ނ����߂�
	int m_CharaGraphX;
	int m_CharaGraphY;

	// ���Ԃɂ���ăL�����̓�����ς���
	int m_FrameChangeChara;

	// �e���[�V�����̃L�����̓����̐�
	int m_CharaMotion;

	// �L�����N�^�[�������Ă��邩�ǂ���
	bool m_NowDash;

	// �L�����N�^�[�����������Ă��邩�ǂ���
	bool m_LookLeft;

	// �L�����N�^�[���W�����v�����Ă���Ƃ�
	bool m_NowJump;

	SceneTitle*m_SceneTitle;
};

