#pragma once
#include "vec2.h"
class MapGimmick
{
public:
	MapGimmick(Vec2 Pos);
	~MapGimmick();

	// ギミック座標取得
	Vec2 GetPos() { return m_Pos; }

	void Init();
	void Update(Vec2 PlayerPos);
	void Draw(Vec2 offset,int handle);
private:
	Vec2 m_Pos;
	float m_FallSpeed;
	
	// 仕掛けのフラグが反応した場合
	bool m_Flag;
};

