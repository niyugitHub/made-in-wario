#pragma once
#include "vec2.h"
class Particle
{
public:
	//パーティクルの最大量
	static constexpr int kMaxParticle = 500;
public:
	Particle();
	~Particle();

	// プレイヤーの座標取得
	void SetPos(Vec2 Pos);

	//エネミーの座標取得
	void SetEnemyPos(Vec2 EnemyPos);

	void Init();

	void SetPlayerParticle();
	void SetEnemyParticle();

	void Update();

	void Draw(Vec2 offset);

private:
	struct Data
	{
		// パーティクルの座標
		Vec2 m_Pos = {0,0};
		// パーティクルの動き
		Vec2 m_Vec = { 0,0 };
		// 色ごとの濃さ
		int m_RColor = 0;
		int m_GColor = 0;
		int m_BColor = 0;
		// 透明度
		int m_Transparency = 0;
		// 存在するかどうか
		bool m_Exist = false;
	};

	int m_Frame;

	Data data[kMaxParticle];

	// 重力
	float m_Gravity;
};

