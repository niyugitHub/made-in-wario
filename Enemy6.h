#pragma once
#include "EnemyBase.h"
class Enemy6 : public EnemyBase
{
public:
	Enemy6();
	~Enemy6();

	/*void SetHp(int Hp) { m_Hp = Hp; }
	int GetHp() { return m_Hp; }*/

	void update();

	void draw(Vec2 offset);
private:
	// �t���[�����Ƃɉ摜��؂�ւ���
	int m_GraphFrame;

	// �U�������ǂ���(�U�����̏ꍇ,�G�̌������ς��Ȃ�)
	bool m_NowAttack;

	void NotUpdate();		// �G����ʊO�ɂ���Ƃ�
	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void UpdateAttack();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy6::* m_func)();
};

