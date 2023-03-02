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

	// タイトルで出すパーティクル
	void SetTitleParticle();
	// プレイヤー回復時パーティクル
	void SetPlayerParticle();
	// プレイヤーがショットを打った時のパーティクル
	void SetShotPlayerParticle();
	// プレイヤーが攻撃されたときパーティクル
	void SetdamagePlayerParticle();
	// エネミーに攻撃ヒット時パーティクル
	void SetEnemyParticle();

	void Update();

	// パーティクルが画面外に出たとき
	bool OffScreen(int i);


	void Draw(Vec2 offset);

	void TitleDraw();

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

		// パーティクルのサイズ
		Vec2 m_ParticleSize = { 0,0 };
	};

	int m_Frame;

	Data data[kMaxParticle];

	// 重力
	float m_Gravity;
};

