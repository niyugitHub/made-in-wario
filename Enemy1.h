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
	// フレームごとにグラフを切り替える
	int m_Frame;

	void NotUpdate();		// 敵が画面外にいるとき
	void UpdatePatrol();	// 通常時
	void UpdateDiscovery();		// プレイヤーが近づいたとき
	void updateAttack();		// プレイヤーに攻撃がヒットしたとき
	// update処理メンバ関数ポインタ
	void(Enemy1::* m_func)();
};

