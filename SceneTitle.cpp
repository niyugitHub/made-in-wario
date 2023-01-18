#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"game.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
}

void SceneTitle::init()
{
//	m_RandColor = 0;
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
	m_player->Init();
}

SceneBase* SceneTitle::update()
{
	/*if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return (new SceneMain);
	}*/

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
	SetFontSize(50);
	DrawString(150, 200, "個人製作", GetColor(0, m_Color, 0));
	DrawString(150, 450, "SPACEを押してスタート", GetColor(0, m_Color, 0));
	m_player->draw();
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
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_IsTitleEnd = true;
		m_player->SetTitle(this);
		m_func = &SceneTitle::FadeoutUpdate;
	}
}

void SceneTitle::FadeoutUpdate()
{
	m_Color -= 8;
}
