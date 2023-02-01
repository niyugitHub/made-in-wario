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
	void UpdatePatrol();	// 通常時
	void UpdateDiscovery();		// プレイヤーが近づいたとき
	void updateAttack();		// プレイヤーに攻撃がヒットしたとき
	// update処理メンバ関数ポインタ
	void(Enemy1::* m_func)();
};

