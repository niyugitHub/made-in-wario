#pragma once
#include "Vec2.h"
#include "ShotBase.h"
class PlayerShot : public ShotBase
{
public:
	PlayerShot(Vec2 Pos, float VecX);
	~PlayerShot();

	void SetHandle(int handle) { m_handle = handle; }
	void SetLookLeft(bool LookLeft) { m_LookLeft = LookLeft; }

	/*void SetPos(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPos() { return m_Pos; }

	void SetVec(float VecX) { m_Vec.x = VecX; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }*/

	void Update();
	void Draw(Vec2 offset);

private:
	int m_handle;

	bool m_LookLeft;
};


