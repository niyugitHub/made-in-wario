#pragma once
#include "EnemyBase.h"
class BossEnemy2 : public EnemyBase
{
public:
	BossEnemy2();
	~BossEnemy2();

	void update();

	void draw(Vec2 offset);

	// iにはグラフの個数を入れる
	void ChangeGraph(int i);

private:
	// 画像
	int m_HpBarHandle1 = -1;
	int m_HpBarHandle2 = -1;
	// 次の攻撃に移るまでの時間(攻撃頻度)
	int m_Frame;

	bool m_NowAttack;

	// HPバー
	int m_HpBar;

	// ジャンプ力
	float m_Jump;

	// フレームごとにグラフを切り替える
	int m_GraphFrame;

	void UpdateNotBattle();	// 戦闘前
	void UpdateDiscovery();		// プレイヤーに近づく
	void UpdateAttack1();		// プレイヤーに攻撃
	void UpdateAttack2();		// プレイヤーに攻撃
	void UpdateAttack3();		// プレイヤーに攻撃
	void UpdateAttack4();		// プレイヤーに攻撃
	void UpdateDead();			// ボス死亡時

	// update処理メンバ関数ポインタ
	void(BossEnemy2::* m_func)();
};

