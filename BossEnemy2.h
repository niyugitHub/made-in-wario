#pragma once
#include "EnemyBase.h"
class BossEnemy2 : public EnemyBase
{
public:
	BossEnemy2();
	~BossEnemy2();

	void update();

	void draw(Vec2 offset);

	// i�ɂ̓O���t�̌�������
	void ChangeGraph(int i);

private:
	// ���̍U���Ɉڂ�܂ł̎���(�U���p�x)
	int m_Frame;

	bool m_NowAttack;

	// �t���[�����ƂɃO���t��؂�ւ���
	int m_GraphFrame;

	void UpdateNotBattle();	// �퓬�O
	void UpdateDiscovery();		// �v���C���[�ɋ߂Â�
	void UpdateAttack1();		// �v���C���[�ɍU��
	void UpdateAttack2();		// �v���C���[�ɍU��
	void UpdateAttack3();		// �v���C���[�ɍU��
	void UpdateAttack4();		// �v���C���[�ɍU��
	void UpdateDead();			// �{�X���S��

	// update���������o�֐��|�C���^
	void(BossEnemy2::* m_func)();
};

