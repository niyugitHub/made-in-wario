#pragma once
#include"GimmickBase.h"
class MapGimmick2 : public GimmickBase
{
public:
	MapGimmick2(Vec2 Pos, int handle);
	~MapGimmick2();

	void Init();
	void Update(Vec2 PlayerPos);
	void Draw(Vec2 offset);
private:
	// �M�~�b�N�̃X�C�b�`�t���[��
	float m_SwitchFrame;
	// �摜�̐؂�ւ��t���[��
	int  m_GraphFrame;

	int m_NextGraph;
};

