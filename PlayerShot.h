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

	// �e�̑��݊m�F


private:
	// �V���b�g���W
	Vec2 m_Pos;
	// �V���b�g�ړ���
	Vec2 m_Vec;

	// �v���C���[�̌���(��)
	bool m_LookLeft;

	// �V���b�g����
	bool m_Exist;
};


