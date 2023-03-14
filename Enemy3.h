#pragma once
#include "EnemyBase.h"

class Enemy3 : public EnemyBase
{
public:
	Enemy3();
	~Enemy3();

	void update();

	void draw(Vec2 offset);

private:
	// フレームごとにグラフを切り替える
	int m_GraphFrame;

	//// 投げたものの位置
	//Vec2 m_ThrowPos;
	// 投げたもののスピード
	float m_FallSpeedX;
	float m_FallSpeedY;

	// 投げる頻度
	int m_RandThrowFrame;

	void NotUpdate();		// 敵が画面外にいるとき
	void UpdatePatrol();	// 通常時
	void UpdateDiscovery();		// プレイヤーが近づいたとき
	void updateAttack();		// プレイヤーに攻撃がヒットしたとき
	// update処理メンバ関数ポインタ
	void(Enemy3::* m_func)();
};

