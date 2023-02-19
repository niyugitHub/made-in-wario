#pragma once
#include "Vec2.h"
#include "ShotBase.h"
class PlayerShot : public ShotBase
{
public:
	PlayerShot(Vec2 Pos, float VecX);
	~PlayerShot();

	/*void SetPos(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPos() { return m_Pos; }

	void SetVec(float VecX) { m_Vec.x = VecX; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }*/

	void Update();
	void Draw(Vec2 offset);
};


