#pragma once
#include"EnemyBase.h"
#include"Vec2.h"
class Enemy2 : public EnemyBase
{
public:
	Enemy2();
	~Enemy2();

	void update();

	void draw();

private:
	int m_Frame;

	float m_FlySpeed;
	float m_FieldSpeed;

	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void updateAttack();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy2::* m_func)();
};

