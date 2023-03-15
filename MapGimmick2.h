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
	// ギミックのスイッチフレーム
	float m_SwitchFrame;
	// 画像の切り替えフレーム
	int  m_GraphFrame;

	int m_NextGraph;
};

