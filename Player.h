#pragma once
#include "Vec2.h"
class Player
{
private:
	static constexpr int kSideSize = 128;
	static constexpr int kColumnSize = 128;

	static constexpr int kSideCharaChipNum = 8;
	static constexpr int kColumnCharaChipNum = 9;
public:
	Player();
	virtual ~Player();

	void Init();
	void end();

	void update();
	void draw();

	// キャラの動きを決める
	void CharaMove();

	// キャラのジャンプ処理
	void CharaJump();

	// グラフィックデータ設定
//	void setHandle(int index, int handle) { m_handle[index] = handle; }

private:
	Vec2 m_pos;
	Vec2 m_vec;

	float m_Jump;

	// グラフの挿入
	int m_handle[kColumnCharaChipNum * kSideCharaChipNum];

	// キャラクターのグラフの種類を決める
	int m_CharaGraphX;
	int m_CharaGraphY;

	// 時間によってキャラの動きを変える
	int m_FrameChangeChara;

	// 各モーションのキャラの動きの数
	int m_CharaMotion;

	// キャラクターが走っているかどうか
	bool m_NowDash;

	// キャラクターが左を向いているかどうか
	bool m_LookLeft;

	// キャラクターがジャンプをしているとき
	bool m_;

