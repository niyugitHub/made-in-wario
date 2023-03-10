#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"
#include <memory>

//class Player;
//class Minigame1;
//class Vec2;
class Collision;
class EnemyFactory;
class Item;
class GameOverScene;
class Option;
class SceneTitle;
class Tutorial;

class SceneMain : public SceneBase
{
//public:
//	enum ItemType
//	{
//		kTwoJump,
//		kAttackUp,
//	};
public:
	static constexpr int kItemNum = 15;
	static constexpr int kStageItemNum = 5;
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	virtual void init();
	// 終了処理
	virtual void end();

	virtual SceneBase* update();
	virtual void draw();

	// アイテムの位置の調整
	void IsItemPosition(int StageNum);

	// プレイヤーの位置調整
	void InitPlayerPos();

	// チュートリアルシーンに移動するか
	bool SceneTutorial();

private:
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();
	void OptionUpdate();
	void TutorialUpdate();

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kCharaChipNum];

	// プレイヤーのポジション
	Vec2 m_PlayerPos;

	// エネミーのポジション
	Vec2 m_EnemyPos;

	// マップのポジション初期化
	Vec2 m_MapPos;

	// アイテムのポジション
	Vec2 m_ItemPos;

	// マップの移動量
	Vec2 m_offset;

	//// キャラクターとブロックの衝突判定
	//bool m_CollTop;
	//bool m_CollBottom;
	//bool m_CollLeft;
	//bool m_CollRight;

	// エネミーとブロックの衝突判定
	bool m_CollTopEnemy;
	bool m_CollBottomEnemy;
	bool m_CollLeftEnemy;
	bool m_CollRightEnemy;

	// プレイヤーの存在確認
	bool m_Exist;

	int m_tempScreenH;

	int m_QuakeFrame = 0;
	float m_QuakeX = 0.0f;

	// アイテムの存在確認
	bool m_ItemExist[kItemNum];

	// アイテムの個数
	int m_ItemNum;
	// 1ステージごとのアイテム個数
	int m_StageItemNum;

	// プレイヤーの攻撃力
	int m_AttackPower;

	// 今どこのステージをプレイしているか
	int m_Stage;

	// 背景の明るさ(フェードイン、フェードアウト時に暗くなる)
	int m_Color;
	
	// プレイヤー
	std::shared_ptr<Player> m_player;

	// マップ
	std::shared_ptr<Map> m_Map;

	// 当たり判定
	std::shared_ptr<Collision> m_Coll;

	// アイテム
	std::shared_ptr<Item> m_Item[kItemNum];

	// 敵全部
	std::shared_ptr<EnemyFactory> m_EnemyFactory;

	// ゲームオーバーシーン
	std::shared_ptr<GameOverScene> m_GameOverScene;

	// オプション画面
	std::shared_ptr< Option> m_Option;

	// チュートリアル
	std::shared_ptr<Tutorial> m_Tutorial;

	// タイトルシーン
	std::shared_ptr<SceneTitle> m_SceneTitle;

	//update処理メンバ関数ポインタ
	void (SceneMain::* m_func)();
};
