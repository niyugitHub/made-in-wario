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
class GameClearScene;
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
	SceneMain(std::shared_ptr<Option> Option );
	virtual ~SceneMain();

	// 初期化
	virtual void init();
	// 終了処理
	virtual void end();

	virtual SceneBase* update();
	virtual void draw();

	void Scroll();

	// アイテムの位置の調整
	void IsItemPosition(int StageNum);

	// プレイヤーの位置調整
	void InitPlayerPos();

	// チュートリアルシーンに移動するか
	bool SceneTutorial();

	// チュートリアルシーンの表示
	void DrawTutorial();

	void TutorialFlag();

	// サウンド
	void Sound();

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

	int m_SwitchFrame = 0;

	// 画像
	int m_OptionHandle = -1;
	int m_TwoJumpTutorialHandle = -1;
	int m_ShotTutorialHandle = -1;
	int m_DamageTutorialHandle = -1;
	// サウンド
	int m_NormalSoundHandle;
	int m_BossSoundHandle;
	int m_GameOverSoundHandle;

	// フォントデータ
	int m_FontHandle = -1;

	//文字の透過度
	int m_StringColor = 0;

	// ゲームオーバーシーンが表示されるまでの時間
	int m_GameOverCount = 0;
	
	// チュートリアル時に処理を止める時間
	int m_TutorialCount = 0;
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

	// ゲームクリアシーン
	std::shared_ptr<GameClearScene> m_GameClearScene;
	// オプション画面
	std::shared_ptr< Option> m_Option;

	// チュートリアル
	std::shared_ptr<Tutorial> m_Tutorial;

	// タイトルシーン
	std::shared_ptr<SceneTitle> m_SceneTitle;

	//update処理メンバ関数ポインタ
	void (SceneMain::* m_func)();
};
