#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include "game.h"
#include "Player.h"
#include<memory>
#include<DxLib.h>

class Particle;
class Option;

class SceneTitle : public SceneBase
{
public:
//	constexpr int kMouseSize = 134;

public:
	SceneTitle()
	{
		m_Pos.x = 0;
		m_Pos.y = 0;
		m_BackgroundPosX = 0;
		m_isEnd = false;
		m_IsTitleEnd = false;
		m_func = &SceneTitle::FadeinUpdate;
		m_textSize = 0;
		m_Color = 0;
		InitSoundMem();

		for (auto& handle : m_hPlayerGraphic)
		{
			handle = -1;
		}

		for (int i = 0; i < Player::kCharaChipNum; i++)
		{
			m_hPlayerGraphic[i] = -1;
		}

		m_player = new Player;

	}
	virtual ~SceneTitle() {}


	virtual void init()override;
	virtual void end() override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

	virtual bool isEnd() { return m_isEnd; }

	virtual bool isTitleEnd() { return m_IsTitleEnd; }

private:
	// Updateメンバ関数
	void FadeinUpdate();
	void TitleSceneUpdate();
	void FadeoutUpdate();
	void OptionUpdate();

	// Drawメンバ関数
	void FirstDraw();
	void NormalDraw();
	void OptionDraw();
	void EndDraw();

private:
	// プレイヤーの位置
	Vec2 m_Pos;

	// 背景のX位置
	int m_BackgroundPosX;
	// テキストのサイズ
	int m_textSize;

	// 何のシーンを選んだか
	int m_SceneNum = 0;

	// 色の濃さ
	int m_Color;

	// ボリューム
	int m_Volum = 0;

	bool m_isEnd;

	bool m_IsTitleEnd;

	// update処理メンバ関数ポインタ
	void(SceneTitle::* m_func)();

	// Draw処理メンバ関数ポインタ
	void(SceneTitle::* m_Drawfunc)();

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kCharaChipNum];

	// 背景のハンドル
	int m_TitleHandle = -1;
	// 背景の文字ハンドル
	int m_TitleStringHandle = -1;

	// サウンドのハンドル
	int m_SoundHandle = -1;

	// オプションのハンドル
	int m_OptionHandle = -1;

	// カーソルの位置
	int m_Cursor = 0;

	// Sceneの終了フラグ
	int m_EndScene = false;
	Player* m_player;

	std::shared_ptr<Particle> m_Particle;
	std::shared_ptr<Option> m_Option;
};