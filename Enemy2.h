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

	void UpdatePatrol();	// 通常時
	void UpdateDiscovery();		// プレイヤーが近づいたとき
	void updateAttack();		// プレイヤーに攻撃がヒットしたとき
	// update処理メンバ関数ポインタ
	void(Enemy2::* m_func)();
};

