#pragma once
#include "Vec2.h"

class SceneTitle;

class Player 
{
public:
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

	Vec2 GetPos() const { return m_pos; }

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

	// グラフィックデータ設定
//	void setHandle(int index, int handle) { m_handle[index] = handle; }

private:
	Vec2 m_pos;
	Vec2 m_vec;

	float m_Jump;

	// グラフの挿入
	int m_handle[kCharaChipNum];

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
	bool m_NowJump;

	SceneTitle*m_SceneTitle;
};

