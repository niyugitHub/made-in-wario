#pragma once
#include "EnemyBase.h"
class Enemy3 : public EnemyBase
{
public:
	Enemy3();
	~Enemy3();

	void update();

	void draw();

private:
	//// ���������̂̈ʒu
	//Vec2 m_ThrowPos;
	// ���������̂̃X�s�[�h
	float m_FallSpeedX;
	float m_FallSpeedY;

	// ������p�x
	int m_RandThrowFrame;

	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void updateAttack();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy3::* m_func)();
};
