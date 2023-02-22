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
	void UpdatePatrol();	// 通常時
	void UpdateDiscovery();		// プレイヤーが近づいたとき
	void updateAttack();		// プレイヤーに攻撃がヒットしたとき
	// update処理メンバ関数ポインタ
	void(Enemy4::* m_func)();
};

