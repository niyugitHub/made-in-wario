#pragma once
#include "EnemyBase.h"
class Enemy4 : public EnemyBase
{
public:
	Enemy4();
	~Enemy4();

	/*void SetHp(int Hp) { m_Hp = Hp; }
	int GetHp() { return m_Hp; }*/

	void update();

private:
	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void updateAttack();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy4::* m_func)();
};

