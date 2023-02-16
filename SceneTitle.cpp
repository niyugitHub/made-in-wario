#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"game.h"
#include"Pad.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
	const char* const kBackgroundGraphic1Filename = "data/Background_01.png";
	const char* const kBackgroundGraphic2Filename = "data/Background_02.png";
}

void SceneTitle::init()
{
//	m_RandColor = 0;
	m_Pos.x = 50;
	m_Pos.y = 800;
	m_isEnd = false;
	m_textSize = 50;
	m_Color = 0;

	m_func = &SceneTitle::FadeinUpdate;

	LoadDivGraph(kPlayerGraphicFilename, Player::kCharaChipNum,
		Player::kSideCharaChipNum, Player::kColumnCharaChipNum,
		Player::kSideSize, Player::kColumnSize, m_hPlayerGraphic);


	for (int i = 0; i < Player::kCharaChipNum; i++)
	{
		m_player->setHandle(i, m_hPlayerGraphic[i]);
	}

	m_BackgroundHandle1 = LoadGraph(kBackgroundGraphic1Filename);
	m_BackgroundHandle2 = LoadGraph(kBackgroundGraphic2Filename);

	m_player->Init();
	m_player->SetPos(m_Pos);
}

SceneBase* SceneTitle::update()
{
	/*if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return (new SceneMain);
	}*/

	m_BackgroundPosX += 3;

	// 画像のサイズより大きくなったら
	if (m_BackgroundPosX > 1969)
	{
		m_BackgroundPosX = 0;
	}

	(this->*m_func)();
	m_player->update();

	if (m_Color <= 0)
	{
		return (new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	DrawGraph(m_BackgroundPosX, 0, m_BackgroundHandle2, true);
	DrawGraph(m_BackgroundPosX, 0, m_BackgroundHandle1, true);
	DrawGraph(m_BackgroundPosX - 1969, 0, m_BackgroundHandle2, true);
	DrawGraph(m_BackgroundPosX - 1969, 0, m_BackgroundHandle1, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(50);
	DrawString(150, 200, "個人製作", GetColor(m_Color, m_Color, 0));
	DrawString(150, 450, "Bを押してスタート", GetColor(m_Color, m_Color, 0));

//	m_player->draw();
}

void SceneTitle::FadeinUpdate()
{
	m_Color += 8;
	if (m_Color >= 255)
	{
		m_Color = 255;
		m_func = &SceneTitle::TitleSceneUpdate;
	}
}

void SceneTitle::TitleSceneUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_IsTitleEnd = true;
		m_player->SetTitle(this);
		m_func = &SceneTitle::FadeoutUpdate;
	}
}

void SceneTitle::FadeoutUpdate()
{
	m_Color -= 9;
}
