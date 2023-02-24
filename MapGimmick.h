#pragma once
#include "vec2.h"
class MapGimmick
{
public:
	MapGimmick(Vec2 Pos);
	~MapGimmick();

	// �M�~�b�N���W�擾
	Vec2 GetPos() { return m_Pos; }

	void Init();
	void Update(Vec2 PlayerPos);
	void Draw(Vec2 offset,int handle);
private:
	Vec2 m_Pos;
	float m_FallSpeed;
	
	// �d�|���̃t���O�����������ꍇ
	bool m_Flag;
};

