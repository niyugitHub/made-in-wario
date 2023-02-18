#pragma once
#include "Vec2.h"
class PlayerShot
{
public:
	PlayerShot();
	~PlayerShot();

	void SetPos(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPos() { return m_Pos; }

	void SetVec(float VecX) { m_Vec.x = VecX; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }

	void SetPlayerLookLeft(bool LookLeft){m_LookLeft = LookLeft;}

	void Update();
	void Draw(Vec2 offset);

	// 弾の存在確認


private:
	// ショット座標
	Vec2 m_Pos;
	// ショット移動量
	Vec2 m_Vec;

	// プレイヤーの向き(左)
	bool m_LookLeft;

	// ショット存在
	bool m_Exist;
};


