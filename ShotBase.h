#pragma once
#include "Vec2.h"
class ShotBase
{
public:
	ShotBase();
	~ShotBase();

	void SetPos(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPos() { return m_Pos; }

	// ショットのサイズセット
	void SetShotSize1(Vec2 ShotSize1) { m_ShotSize1 = ShotSize1; }
	void SetShotSize2(Vec2 ShotSize2) { m_ShotSize2 = ShotSize2; }

	Vec2 GetShotSize1() { return m_ShotSize1; }
	Vec2 GetShotSize2() { return m_ShotSize2; }

	// ショットのハンドル
	void SetHandle(int handle) { m_handle = handle; }

	// ショットの向き
	void SetLookShot(int LookShot) { m_LookShot = LookShot; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }

	virtual void Update(Vec2 PlayerPos);
	virtual void Draw(Vec2 offset);

protected:
	// ショット座標
	Vec2 m_Pos;
	// ショット移動量
	Vec2 m_Vec;

	Vec2 m_ShotSize1;
	Vec2 m_ShotSize2;

	// ショット存在
	bool m_Exist;

	// ショットのハンドル
	int m_handle;

	//ショットの向き
	int m_LookShot;

	// 画像の種類
	int m_GraphX;
	int m_GraphY;

	int m_Frame;
};


