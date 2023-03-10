#pragma once
#include "Vec2.h"
#include <memory>

class Map;

class Item
{
public:
	enum ItemType
	{
		kTwoJump,
		kAttackUp,
		kHpUp,
		kGaugeUp,
		kShot,
	};
public:
	Item();
	~Item();

	void SetMap(std::shared_ptr<Map> map) { m_Map = map; }
	void SetPos(Vec2 pos) { m_Pos = pos; }

	void SetHandle(int handle) { m_handle = handle; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }

	void SetItemNum(int Num) { m_ItemNum = Num; }
	int GetItemType() { return m_ItemType; }

	Vec2 GetPos() { return m_Pos; }

	void Init(int count);

	void Update();

	void Draw(Vec2 offset);

private:
	// �A�C�e���̔ԍ�
	int m_ItemNum;

	int m_handle;
	// �A�C�e���̃^�C�v
	int m_ItemType;

	// �A�C�e���̓���
	float m_Move;
	float m_Acceleration;
	std::shared_ptr<Map> m_Map;

	Vec2 m_Pos;

	bool m_Exist;
};

