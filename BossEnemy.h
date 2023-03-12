#pragma once
#include "EnemyBase.h"
class BossEnemy : public EnemyBase
{
public:
	BossEnemy();
	~BossEnemy();

	void update();

	void draw(Vec2 offset);

	// iにはグラフの個数を入れる
	void ChangeGraph(int i);

private:
	// 戦闘開始
	bool m_StartBattle = false;

	// 次の攻撃に移るまでの時間(攻撃頻度)
	int m_Frame;

	bool m_NowAttack;

	// フレームごとにグラフを切り替える
	int m_GraphFrame;

	void UpdateNotBattle();	// 戦闘前
	void UpdateDiscovery();		// プレイヤーに近づく
	void UpdateAttack1();		// プレイヤーに攻撃
	void UpdateAttack2();		// プレイヤーに攻撃
	void UpdateAttack3();		// プレイヤーに攻撃
	void UpdateAttack4();		// プレイヤーに攻撃
	// update処理メンバ関数ポインタ
	void(BossEnemy::* m_func)();
};

