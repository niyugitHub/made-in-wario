#pragma once
#include "GimmickBase.h"
#include "Vec2.h"
class MapGimmick3 : public GimmickBase
{
public:
	MapGimmick3(Vec2 Pos, int handle);
	~MapGimmick3();

	void Init();
	void Update(Vec2 PlayerPos);
	void Draw(Vec2 offset);
private:
	Vec2 m_BloakPos; // 中心の座標
	float m_Rota; // 回転の角度

};

