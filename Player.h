#pragma once
#include "Vec2.h"
#include<memory>

class Map;
class SceneTitle;
class PlayerShot;
class Particle;

class Player 
{
public:
	// プレイヤーの初期位置
	static constexpr float kFristPlayerPosX = 760.0f;
	static constexpr float kFristPlayerPosY = 800.0f;

	static constexpr int kSideSize = 128;
	static constexpr int kColumnSize = 128;

	static constexpr int kSideCharaChipNum = 8;
	static constexpr int kColumnCharaChipNum = 9;

	static constexpr int kCharaChipNum = kSideCharaChipNum * kColumnCharaChipNum;

	// ノックバック(攻撃を受けたとき)のスピード
	static constexpr float kKnockBackSpeed = 12.0f;
	// ノックバック(攻撃を当てたとき)のスピード
	static constexpr float kHitKnockBackSpeed = 6.0f;
public:
	Player();
	virtual ~Player();

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	void setMap(std::shared_ptr<Map> pMap) { m_Map = pMap; }
	void SetTitle(SceneTitle* pTitle) { m_SceneTitle = pTitle; }

	void SetPos(Vec2 pos) { m_pos = pos; }

	void SetCollTop(bool Top) { m_CollTop = Top; }
	void SetCollBottom(bool Bottom) { m_CollBottom = Bottom; }
	void SetCollRight(bool Right) { m_CollRight = Right; }
	void SetCollLeft(bool Left) { m_CollLeft = Left; }

	void SetCollItemTwoJump(bool TwoJump) { m_PossibleTwoJump = TwoJump; }

	void SetExist(bool Exist) { m_Exist = Exist; }
	bool GetExist() { return m_Exist; }

	// ダメージを受けたフラグをセット
	void SetDamage(bool Damage) { m_Damage = Damage; }
	bool GetDamage() { return m_Damage; }

	Vec2 GetPos() const { return m_pos; }

	Vec2 GetNextPos()const { return m_NextPos; }

	//ショットの座標
	void SetShotPos(Vec2 ShotPos) { m_ShotPos = ShotPos; }
	Vec2 GetShotPos() { return m_ShotPos; }

	void SetAttackPower(int AttackPower) { m_AttackPower = AttackPower; }
	int GetAttackPower() { return m_AttackPower; }

	float GetMove() const { return m_StartMove; }

	// プレイヤーの攻撃判定と向きを返す
	bool GetAttack() { return m_Attack; }
	bool GetLook() { return m_LookLeft; }

	//// 攻撃ヒット確認 もしm_HitAttackがtrueの場合敵に攻撃が当たらない(連続で敵にヒットするのを防ぐため)
	//void SetHitAttack(bool HitAttack) { m_HitAttack = HitAttack; }
	bool GetInitAttack() { return m_InitAttack; }

	// 無敵時間
	void SetNoDamageFrame(int NoDamage) { m_NoDamageFrame = NoDamage; }
	int GetNoDamageFrame() { return m_NoDamageFrame; }

	// ステージクリア
	void SetStageClaer(bool StageClaer) { m_StageClear = StageClaer; }
	bool GetStageClaer() { return m_StageClear; }

	// 敵座標取得
	void SetEnemyPos(Vec2 EnemyPos) { m_EnemyPos = EnemyPos; };

	// ショットアイテムを取得したときショットを打てるように
	void SetShot(bool PossibleShot) { m_PossibleShot = PossibleShot; }

	// ノックバックスピード取得
	void SetKnockBackSpeed(float KnockbackSpeed){m_KnockBack = KnockbackSpeed;}

	void Init();
	void end();

	void update();
	void draw(Vec2 offset);

	// キャラの動きを決める
	void CharaMove();

	// キャラのジャンプ処理
	void CharaJump();

	// 動きの制限
	void LimitMove();

	// プレイヤーが死んだときの処理
	void NotExist();

	// プレイヤーの動き初めの処理
	void IsMoveStart();

	// プレイヤーが止まったときの処理
	void IsMoveStop();

	//// 敵の攻撃が当たった時
	void Ondamage();

	// ノックバック処理
	void IsKnockBack(Vec2 EnemyPos);

	// 回復処理
	void IsActiveGauge();

	// ゲージ
	void IsGauge();

	// 当たり判定
	void IsColl();

	// ショットの当たり判定
	bool IsShotColl();
	
	//当たり判定初期化
	void InitColl();

	//ボタン押してるか確認
	bool PushButton();

	// プレイヤーが落下したかどうか
	bool FallPlayer();

	// MaxHp増加
	void MaxHpUp();

	// MaxGauge増加
	void MaxGaugeUp();

	// ギミックに当たったとき
	void CollGimmick();

	// トゲに当たったとき
	bool CollNeedle();
	// サウンド
	void IsSound();

	// グラフィックデータ設定
//	void setHandle(int index, int handle) { m_handle[index] = handle; }

private:
	// 現在の座標
	Vec2 m_pos;
	// 次フレーム時の座標
	Vec2 m_NextPos;

	Vec2 m_vec;

	// 敵座標取得
	Vec2 m_EnemyPos;

	// ショットの座標取得
	Vec2 m_ShotPos;

	float m_StartMove;

	float m_Jump;

	// グラフの挿入
	int m_handle[kCharaChipNum];
	int m_Hphandle;
	int m_Gaugehandle;
	int m_Gauge1handle;
	int m_Shothandle;

	// 音ハンドルの追加
	int m_SoundAttack = -1;
	int m_SoundJump = -1;
	int m_SoundWalk = -1;
	int m_SoundDash = -1;
	int m_SoundDamage = -1;
	int m_SoundHeal = -1;
	int m_SoundHealCompleted = -1;
	int m_SoundShot = -1;

	// キャラクターのグラフの種類を決める
	int m_CharaGraphX;
	int m_CharaGraphY;

	// 時間によってキャラの動きを変える
	int m_FrameChangeChara;

	// キャラの動きを変える速度
	int m_FrameChangeSpeed;

	// 各モーションのキャラの動きの数
	int m_CharaMotion;

	// キャラクターの重力
	float m_Gravity;

	// キャラクターが走っているかどうか
	bool m_NowDash;

	// キャラクターが左を向いているかどうか
	bool m_LookLeft;

	// キャラクターがジャンプをしているとき
	bool m_NowJump;

	// キャラクターが二段ジャンプしているとき
	bool m_TwoJump;

	// キャラクターが二段ジャンプを使ったとき
	bool m_UseTwoJump;

	// キャラクターが地面についているかどうか
	bool m_Coll_Ground;

	// キャラクターとブロックの衝突判定
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	// プレイヤーとアイテムが触れたとき(二段ジャンプ)
	bool m_PossibleTwoJump;

	// キャラクターが攻撃をしたとき
	bool m_Attack;

	// 攻撃がヒットしたとき
	bool m_InitAttack;

	// プレイヤーの攻撃力　
	int m_AttackPower;

	// プレイヤーの体力
	int m_Hp;
	// プレイヤーの最大体力
	int m_MaxHp;

	// プレイヤーの無敵時間
	int m_NoDamageFrame;

	// ノックバックスピード
	float m_KnockBack;

	// ボタンを押した時間
	int m_PushFrame;

	// ゲージ量
	int m_Gauge;

	//Maxゲージ
	int m_MaxGauge;

	// ゲージの減少(見た目をよくするための変数)
	int m_MinusGauge = 0;

	// ショットを打てるかどうか
	bool m_PossibleShot;
	// ショット間隔
	int m_ShotIntervalFrame;
	// ショットを打ったかどうか
//	bool m_Shot;

	// ダメージを食らったフラグ
	bool m_Damage = false;

	// ステージをクリアしたとき
	bool m_StageClear;

	// キャラクターの存在確認
	bool m_Exist;

	std::shared_ptr<Map> m_Map;
	SceneTitle* m_SceneTitle;
	PlayerShot* m_Shot;
	std::shared_ptr<Particle> m_Particle;
};

