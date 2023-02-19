#pragma once
#include "Vec2.h"
class ShotBase
{
public:
	ShotBase();
	~ShotBase();

	void SetPos(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPos() { return m_Pos; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }

	virtual void Update();
	virtual void Draw(Vec2 offset);

protected:
	// ショット座標
	Vec2 m_Pos;
	// ショット移動量
	Vec2 m_Vec;

	// ショット存在
	bool m_Exist;
};


