#pragma once
#include "vec2.h"
class MapGimmick
{
public:
	MapGimmick(Vec2 Pos);
	~MapGimmick();

	void Init();
	void Update();
	void Draw(int handle);
private:
	Vec2 m_Pos;
	float m_FallSpeed;
	
	// 仕掛けのフラグが反応した場合
	bool Flag;
};

