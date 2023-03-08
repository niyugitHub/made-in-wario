#include "GameOverScene.h"
#include "Pad.h"
#include <DxLib.h>

namespace
{
	const char* const kGameOverSceneGraphicFilename = "data/GameOverScene.png";

	// カーソルの初期位置
	constexpr int kCursorNumX = 550;
	constexpr int kCursorNumY = 600;

	// フェードイン、フェードアウトの速さ
	constexpr int kFadeSpeed = 8;
}

GameOverScene::GameOverScene() : 
	m_SceneNum(0),
	m_PlayAgain(false),
	m_Abort(false),
	m_ActiveGameOver(false)
{
	m_Handle = LoadGraph(kGameOverSceneGraphicFilename);
	m_func = &GameOverScene::FadeinUpdate;
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
	m_SceneNum = 0;
	m_CursorMove = 0;
	m_PlayAgain = false;
	m_Abort = false;
	m_Color = 0;
	m_ActiveGameOver = true;
	m_func = &GameOverScene::FadeinUpdate;
}

void GameOverScene::Update()
{
	(this->*m_func)();
}

void GameOverScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);

	DrawGraph(0, 0,m_Handle, true);
	DrawString(kCursorNumX, kCursorNumY + m_CursorMove, "→", 0xffffff,true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::FadeinUpdate()
{
	if (m_Color < 255)
	{
		m_Color += kFadeSpeed;
		if (m_Color >= 255)
		{
			m_Color = 255;
			m_func = &GameOverScene::NormalUpdate;
		}
	}
}

void GameOverScene::NormalUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		if (m_SceneNum == 0)
		{
			m_SceneNum++;
		}

		else if (m_SceneNum == 1)
		{
			m_SceneNum--;
		}
	}

	if (m_SceneNum == 0)
	{
		m_CursorMove -= 10;
		if (m_CursorMove <= 0)
		{
			m_CursorMove = 0;
		}
	}

	if (m_SceneNum == 1)
	{
		m_CursorMove += 10;
		if (m_CursorMove >= 150)
		{
			m_CursorMove = 150;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_func = &GameOverScene::FadeoutUpdate;
	}
}

void GameOverScene::FadeoutUpdate()
{
	m_Color -= kFadeSpeed;
	
	if (m_Color <= 0)
	{
		if (m_SceneNum == 0) m_PlayAgain = true;

		if (m_SceneNum == 1) m_Abort = true;
	}
}
