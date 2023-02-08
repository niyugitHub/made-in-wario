#pragma once
#include "Vec2.h"

class SceneTitle;

class Collision;

class Player 
{
public:
	// プレイヤーの初期位置
	static constexpr float kFristPlayerPosX = 760.0f;
	static constexpr float kFristPlayerPosY = 500.0f;

	static constexpr int kSideSize = 128;
	static constexpr int kColumnSize = 128;

	static constexpr int kSideCharaChipNum = 8;
	static constexpr int kColumnCharaChipNum = 9;

	static constexpr int kCharaChipNum = kSideCharaChipNum * kColumnCharaChipNum;
public:
	Player();
	virtual ~Player();

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	void SetTitle(SceneTitle* pTitle) { m_SceneTitle = pTitle; }

	void SetPos(Vec2 pos) { m_pos = pos; }

	void SetCollTop(bool Top) { m_CollTop = Top; }
	void SetCollBottom(bool Bottom) { m_CollBottom = Bottom; }
	void SetCollRight(bool Right) { m_CollRight = Right; }
	void SetCollLeft(bool Left) { m_CollLeft = Left; }

	void SetCollItemTwoJump(bool TwoJump) { m_PossibleTwoJump = TwoJump; }

	void SetExist(bool Exist) { m_Exist = Exist; }

	Vec2 GetPos() const { return m_pos; }

	void SetAttackPower(int AttackPower) { m_AttackPower = AttackPower; }
	int GetAttackPower() { return m_AttackPower; }

	int GetMove() const { return m_StartMove; }

	// プレイヤーの攻撃判定と向きを返す
	bool GetAttack() { return m_Attack; }
	bool GetLook() { return m_LookLeft; }

	void Init();
	void end();

	void update();
	void draw();

	// キャラの動きを決める
	void CharaMove();

	// キャラのジャンプ処理
	void CharaJump();

	// 動きの制限
	void LimitMove();

	// プレイヤーが死んだときの処理
	void NotExist();

	// プレイヤーの動き初めの処理
	void IsMoveStartLeft();

	// プレイヤーの動き初めの処理
	void IsMoveStartRight();

	// プレイヤーが止まったときの処理
	void IsMoveStop();

	// グラフィックデータ設定
//	void setHandle(int index, int handle) { m_handle[index] = handle; }

private:
	Vec2 m_pos;
	Vec2 m_vec;

	float m_StartMove;

	float m_Jump;

	// グラフの挿入
	int m_handle[kCharaChipNum];

	// キャラクターのグラフの種類を決める
	int m_CharaGraphX;
	int m_CharaGraphY;

	// 時間によってキャラの動きを変える
	int m_FrameChangeChara;

	// キャラの動きを変える速度
	int m_FrameChangeSpeed;

	// 各モーションのキャラの動きの数
	int m_CharaMotion;

	// キャラクターの重力
	float m_Gravity;

	// キャラクターが走っているかどうか
	bool m_NowDash;

	// キャラクターが左を向いているかどうか
	bool m_LookLeft;

	// キャラクターがジャンプをしているとき
	bool m_NowJump;

	// キャラクターが二段ジャンプしているとき
	bool m_TwoJump;

	// キャラクターが二段ジャンプを使ったとき
	bool m_UseTwoJump;

	// キャラクターが地面についているかどうか
	bool m_Coll_Ground;

	// キャラクターとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	// プレイヤーとアイテムが触れたとき(二段ジャンプ)
	bool m_PossibleTwoJump;

	// キャラクターが攻撃をしたとき
	bool m_Attack;

	// 動きを開始したときのフラグ
	bool m_IsMove;

	// プレイヤーの攻撃力　
	int m_AttackPower;

	// プレイヤーの体力
	int m_Hp;

	// キャラクターの存在確認
	bool m_Exist;

	SceneTitle* m_SceneTitle;
};

