#pragma once
#include"EnemyBase.h"
#include"Vec2.h"
class Enemy2 : public EnemyBase
{
public:
	Enemy2();
	~Enemy2();

	void update();

	void draw(Vec2 offset);

private:
	int m_Frame;

	// �t���[�����ƂɃO���t��؂�ւ���
	int m_GraphFrame;

	float m_FlySpeed;
	float m_FieldSpeed;

	void NotUpdate();		// �G����ʊO�ɂ���Ƃ�
	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void updateAttack();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy2::* m_func)();
};

