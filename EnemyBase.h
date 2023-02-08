#include"Vec2.h"
#include<memory>
#pragma once

class Map;
class Player;
class Collision;

class EnemyBase
{
public:
	static constexpr float kGravity = 0.05f;
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void SetMap(std::shared_ptr<Map> pMap) { m_Map = pMap; }
	virtual void SetPlayer(std::shared_ptr<Player> pPlayer) { m_Player = pPlayer; }
	virtual void SetColl(std::shared_ptr<Collision> Coll) { m_Coll = Coll; }

	virtual void SetCollTop(bool Top) { m_CollTop = Top; }
	virtual void SetCollBottom(bool Bottom) { m_CollBottom = Bottom; }
	virtual void SetCollRight(bool Right) { m_CollRight = Right; }
	virtual void SetCollLeft(bool Left) { m_CollLeft = Left; }

	virtual void SetPos(Vec2 Pos) { m_Pos = Pos; }

	// エネミーの体力
	void SetHp(int Hp) { m_Hp = Hp; }
	int GetHp() { return m_Hp; }

	// 攻撃がヒット
	bool SetHit(bool HitAttack) {  HitAttack; }

	virtual void Init();
	virtual void end();

	virtual Vec2 GetPos() { return m_NextPos; }

	virtual void update();
	virtual void draw();

	virtual void MoveEnemy();

	virtual void BasicMoveEnemy();

	// 存在確認
	bool isExist() const { return m_Exist; }
	void setExist(bool isExist) { m_Exist = isExist; }

protected:
	// 現在のエネミーのポジション
	Vec2 m_Pos;
	// 移動量
	Vec2 m_Vec;

	// 次のフレームのエネミーのポジション
	Vec2 m_NextPos;

	// プレイヤーの座標
	Vec2 m_PlayerPos;

	// プレイヤーとエネミーの座標の差
	Vec2 m_DistancePos;

	float m_Gravity;

	int m_Hp; // 敵の体力

	// 壁に当たった時に逆方向に進むための変数
	int m_MoveInverseDirection;

	// スクロールのスピード
	Vec2 m_MapVec;

	// 死亡判定
	bool m_Exist;

	// エネミーとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	bool m_HitAttack

	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Collision> m_Coll;

};

