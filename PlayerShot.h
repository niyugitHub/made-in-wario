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

	void Update();
	void Draw(Vec2 offset);

private:
	// �V���b�g���W
	Vec2 m_Pos;
	// �V���b�g�ړ���
	Vec2 m_Vec;

	// �V���b�g����
	bool m_Exist;
};

