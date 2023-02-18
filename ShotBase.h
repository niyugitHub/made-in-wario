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
	// �V���b�g���W
	Vec2 m_Pos;
	// �V���b�g�ړ���
	Vec2 m_Vec;

	// �V���b�g����
	bool m_Exist;
};


