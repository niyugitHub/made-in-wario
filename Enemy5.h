#pragma once
#include "EnemyBase.h"
#include"Vec2.h"

class Enemy5 : public EnemyBase
{
public:
	Enemy5();
	~Enemy5();

	void update();

	void draw(Vec2 offset);

private:
	int m_Frame;

	// フレームごとにグラフを切り替える
	int m_GraphFrame;
	
	// ショットを打つまでのフレーム
	int m_ShotFrame;
	int m_NextShotFrame;

	float m_FlySpeed;
	float m_FieldSpeed;

	void NotUpdate();		// 敵が画面外にいるとき
	void UpdatePatrol();	// 通常時
	void UpdateDiscovery();		// プレイヤーが近づいたとき
	void UpdateAttackShot();		// プレイヤーに攻撃がヒットしたとき
	// update処理メンバ関数ポインタ
	void(Enemy5::* m_func)();
};

