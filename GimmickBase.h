#pragma once
#include "vec2.h"
class GimmickBase
{
public:
	GimmickBase();
	~GimmickBase();

	// ギミック座標取得
	virtual Vec2 GetPos() { return m_Pos; }

	// グラフサイズ取得
	virtual Vec2 GetGraphSize() { return m_GraphSize; }
	
	virtual void Init();
	virtual void Update(Vec2 PlayerPos);
	virtual void Draw(Vec2 offset);

protected:
	Vec2 m_Pos;

	int m_handle;

	// どこのグラフを表示させるか
	int m_GraphX;
	int m_GraphY;

	Vec2 m_offset;

	// グラフサイズ
	Vec2 m_GraphSize;

	// 仕掛けのフラグが反応した場合
	bool m_Flag;
};

