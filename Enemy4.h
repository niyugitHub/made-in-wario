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
	void draw(Vec2 offset);

private:
	// �W�����v��
	float m_JumpPower;
	// �W�����v�Ԋu
	int m_JumpFrame;
	// �X�s�[�h
	float m_Speed;
	//// �摜�̎��
	//int m_GraphX;
	//int m_GraphY;

	void UpdateGraph();

	void UpdatePatrol();	// �ʏ펞
	
	// update���������o�֐��|�C���^
	void(Enemy4::* m_func)();
};

