#pragma once
#include "vec2.h"
class MapGimmick
{
public:
	MapGimmick(Vec2 Pos , int handle);
	~MapGimmick();

	// ギミック座標取得
	Vec2 GetPos() { return m_Pos; }

	void Init();
	void Update(Vec2 PlayerPos);
	void Draw(Vec2 offset);
private:
	Vec2 m_Pos;
	int m_handle;
	float m_FallSpeed;
	
	// 仕掛けのフラグが反応した場合
	bool m_Flag;
};

