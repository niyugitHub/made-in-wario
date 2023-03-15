#pragma once
#include "vec2.h"
class GimmickBase
{
public:
	GimmickBase();
	~GimmickBase();

	// ギミック座標取得
	virtual Vec2 GetPos() { return m_Pos; }

	// ギミックが作動中かどうか
	virtual bool GetFlag() { return m_Flag; }
	// グラフのサイズ取得
	virtual Vec2 GetGraphSize1() { return m_GraphSize1; }
	virtual Vec2 GetGraphSize2() { return m_GraphSize2; }
	
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
	Vec2 m_GraphSize1;
	Vec2 m_GraphSize2;

	// 仕掛けのフラグが反応した場合
	bool m_Flag;
};

