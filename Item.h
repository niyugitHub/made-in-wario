#pragma once
#include "Vec2.h"
#include <memory>

class Map;

class Item
{
public:
	Item();
	~Item();

	void SetMap(std::shared_ptr<Map> map) { m_Map = map; }
	void SetPos(Vec2 pos) { m_Pos = pos; }

	Vec2 GetPos() { return m_Pos; }

	void Init();

	void Update();

	void Draw();

private:
	std::shared_ptr<Map> m_Map;

	Vec2 m_Pos;
};

