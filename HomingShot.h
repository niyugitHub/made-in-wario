#pragma once
#include "ShotBase.h"
class HomingShot : public ShotBase
{
public:
	HomingShot(Vec2 Pos, Vec2 Vec);
	~HomingShot();

	/*void SetPos(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPos() { return m_Pos; }*/

	//	void SetVec(float VecX) { m_Vec.x = VecX; }

	//	void SetMapVec(Vec2 MapVec) { m_MapVec = MapVec; }

		/*void SetExist(bool Exist) { m_Exist = Exist; }
		bool GetExist() { return m_Exist; }*/

	void Update(Vec2 PlayerPos);
	void Draw(Vec2 offset);

private:
	
};

