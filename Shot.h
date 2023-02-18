#pragma once
#include "ShotBase.h"

class Shot : public ShotBase
{
public:
	Shot(Vec2 Pos,float VecX);
	~Shot();

	/*void SetPos(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPos() { return m_Pos; }*/

//	void SetVec(float VecX) { m_Vec.x = VecX; }

//	void SetMapVec(Vec2 MapVec) { m_MapVec = MapVec; }

	/*void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }*/

	void Update();
	void Draw(Vec2 offset);

private:
	//Vec2 m_Pos;

	//Vec2 m_Vec;

	// マップの移動量
	Vec2 m_MapVec;
};

