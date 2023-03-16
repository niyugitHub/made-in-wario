#pragma once
#include "EnemyBase.h"
class Enemy6 : public EnemyBase
{
public:
	Enemy6();
	~Enemy6();

	/*void SetHp(int Hp) { m_Hp = Hp; }
	int GetHp() { return m_Hp; }*/

	void update();

	void draw(Vec2 offset);
private:
	// フレームごとに画像を切り替える
	int m_GraphFrame;

	// 攻撃中かどうか(攻撃中の場合,敵の向きが変わらない)
	bool m_NowAttack;

	void NotUpdate();		// 敵が画面外にいるとき
	void UpdatePatrol();	// 通常時
	void UpdateDiscovery();		// プレイヤーが近づいたとき
	void UpdateAttack();		// プレイヤーに攻撃がヒットしたとき
	// update処理メンバ関数ポインタ
	void(Enemy6::* m_func)();
};

