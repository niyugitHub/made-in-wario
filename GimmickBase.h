#pragma once
#include "vec2.h"
class GimmickBase
{
public:
	GimmickBase();
	~GimmickBase();

	// �M�~�b�N���W�擾
	virtual Vec2 GetPos() { return m_Pos; }

	// �O���t�T�C�Y�擾
	virtual Vec2 GetGraphSize() { return m_GraphSize; }
	
	virtual void Init();
	virtual void Update(Vec2 PlayerPos);
	virtual void Draw(Vec2 offset);

protected:
	Vec2 m_Pos;

	int m_handle;

	// �ǂ��̃O���t��\�������邩
	int m_GraphX;
	int m_GraphY;

	Vec2 m_offset;

	// �O���t�T�C�Y
	Vec2 m_GraphSize;

	// �d�|���̃t���O�����������ꍇ
	bool m_Flag;
};

