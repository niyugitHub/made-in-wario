#pragma once
#include "EnemyBase.h"
#include"Vec2.h"

class Enemy5 : public EnemyBase
{
public:
	Enemy5();
	~Enemy5();

	void update();

	void draw(Vec2 offset);

private:
	int m_Frame;

	// �t���[�����ƂɃO���t��؂�ւ���
	int m_GraphFrame;
	
	// �V���b�g��ł܂ł̃t���[��
	int m_ShotFrame;
	int m_NextShotFrame;

	float m_FlySpeed;
	float m_FieldSpeed;

	void NotUpdate();		// �G����ʊO�ɂ���Ƃ�
	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void UpdateAttackShot();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy5::* m_func)();
};

