#pragma once
#include "Vec2.h"
class ShotBase
{
public:
	ShotBase();
	~ShotBase();

	Vec2 GetPos() { return m_Pos; }

	void Update();
	void Draw(Vec2 offset);

private:
	// ショット座標
	Vec2 m_Pos;
	// ショット移動量
	Vec2 m_Vec;

	// ショット存在
	bool m_Exist;
};


