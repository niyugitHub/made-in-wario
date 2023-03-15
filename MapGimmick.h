#pragma once
#include "vec2.h"
#include "GimmickBase.h"
class MapGimmick : public GimmickBase
{
public:
	MapGimmick(Vec2 Pos , int handle);
	~MapGimmick();

	void Init();
	void Update(Vec2 PlayerPos);
	void Draw(Vec2 offset);
private:

	float m_FallSpeed;
};

