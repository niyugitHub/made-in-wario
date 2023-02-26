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
	// ジャンプ力
	float m_JumpPower;
	// ジャンプ間隔
	int m_JumpFrame;
	// スピード
	int m_Speed;

	void UpdatePatrol();	// 通常時
	
	// update処理メンバ関数ポインタ
	void(Enemy4::* m_func)();
};

