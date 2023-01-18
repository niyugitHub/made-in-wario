#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"game.h"

void SceneTitle::init()
{
//	m_RandColor = 0;
	m_isEnd = false;
	m_textSize = 50;
	m_Color = 0;

	m_func = &SceneTitle::FadeinUpdate;
}

SceneBase* SceneTitle::update()
{
	/*if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return (new SceneMain);
	}*/

	(this->*m_func)();

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
		m_func = &SceneTitle::FadeoutUpdate;
	}
}

void SceneTitle::FadeoutUpdate()
{
	m_Color -= 8;
}
