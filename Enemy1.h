#pragma once
#include"EnemyBase.h"

//class Map;

class Enemy1 : public EnemyBase
{
public:
	Enemy1();
	~Enemy1();

	/*void SetHp(int Hp) { m_Hp = Hp; }
	int GetHp() { return m_Hp; }*/

	 void update();

	 void draw(Vec2 offset);
private:
	// �t���[�����ƂɃO���t��؂�ւ���
	int m_Frame;

	void NotUpdate();		// �G����ʊO�ɂ���Ƃ�
	void UpdatePatrol();	// �ʏ펞
	void UpdateDiscovery();		// �v���C���[���߂Â����Ƃ�
	void updateAttack();		// �v���C���[�ɍU�����q�b�g�����Ƃ�
	// update���������o�֐��|�C���^
	void(Enemy1::* m_func)();
};

