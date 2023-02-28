#pragma once
#include"Vec2.h"
#include<memory>
#include "ShotBase.h"

class Map;
class Player;
class Collision;
class FallShot;
class HomingShot;

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

	// グラフをセット
	virtual void SetHandle(int handle) { m_handle = handle; }

	// ショットのグラフをセット
	virtual void SetShotHandle(int Shothandle) { m_Shothandle = Shothandle; }

	// 攻撃がヒット
	void SetHit(bool HitAttack) { m_HitAttack = HitAttack; }
	bool GetHit() { return m_HitAttack; }

	virtual void Init();
	virtual void end();

	// 敵座標取得
	virtual Vec2 GetPos() { return m_NextPos; }

	// 敵が投げた物の座標取得
	virtual Vec2 GetThrowPos() { return m_ThrowPos; }

	// グラフのサイズ取得
	virtual Vec2 GetGraphSize() { return m_GraphSize; }

	virtual void update();
	virtual void draw(Vec2 offset);

	virtual void MoveEnemy();

	virtual void BasicMoveEnemy();

	virtual void InitKnockBack(); // ノックバックのスピードを初期化

	virtual void KnockBack(); // ノックバック処理

	virtual void OnDamage(int damage); // ダメージを受けた時の処理

	virtual bool CollThrow(); // ショットとプレイヤーの当たり判定

	// プレイヤーが放ったショットとエネミーの当たり判定
	virtual bool CollShotPlayer(); 

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

	// 投げ物の座標
	Vec2 m_ThrowPos;

	// プレイヤーの座標
	Vec2 m_PlayerPos;

	// プレイヤーとエネミーの座標の差
	Vec2 m_DistancePos;

	// エネミーの画像ハンドル
	int m_handle;
	// ショットの画像ハンドル
	int m_Shothandle;

	float m_Gravity;

	int m_Hp; // 敵の体力

	bool m_HitAttack; // プレイヤーの攻撃がヒットしたとき

	float m_KnockBackSpeed; // ノックバックのスピード
	float m_MaxKnockBackSpeed; // ノックバック時の最大スピード

	// 壁に当たった時に逆方向に進むための変数
	int m_MoveInverseDirection;

	// スクロールのスピード
	Vec2 m_MapVec;

	// 死亡判定
	bool m_Exist;

	// エネミーの向き(-1:左 1:右)
	int m_LookEnemy;

	// 画像の種類
	int m_GraphX;
	int m_GraphY;

	// 画像のグラフサイズ取得
	Vec2 m_GraphSize;

	// エネミーとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Collision> m_Coll;
	ShotBase* m_Shot;
};

