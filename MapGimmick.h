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
	
	// dŠ|‚¯‚Ìƒtƒ‰ƒO‚ª”½‰‚µ‚½ê‡
	bool Flag;
};

