#pragma once
#include"EnemyBase.h"

class Map;

class Enemy1 : public EnemyBase
{
public:
	Enemy1();
	~Enemy1();

	 void update();

private:
	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void updateAttack();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy1::* m_func)();
};

