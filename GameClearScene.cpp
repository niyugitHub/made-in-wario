#include "GameClearScene.h"
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

GameClearScene::GameClearScene(int handle) : 
	m_handle(handle),
	m_Cursor(0),
	m_CursorMove(0),
	m_PlayAgain(false),
	m_Abort(false),
	m_Color(0)
{
	m_func = &GameClearScene::FadeinUpdate;
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::Init()
{
}

void GameClearScene::Update()
{
	(this->*m_func)();
}

void GameClearScene::Draw()
{
}

void GameClearScene::FadeinUpdate()
{
	if (m_Color < 255)
	{
		m_Color += kFadeSpeed;
		if (m_Color >= 255)
		{
			m_Color = 255;
			m_func = &GameClearScene::NormalUpdate;
		}
	}
}

void GameClearScene::NormalUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		if (m_Cursor == 0)
		{
			m_Cursor++;
		}

		else if (m_Cursor == 1)
		{
			m_Cursor--;
		}
	}

	if (m_Cursor == 0)
	{
		m_CursorMove -= 10;
		if (m_CursorMove <= 0)
		{
			m_CursorMove = 0;
		}
	}

	if (m_Cursor == 1)
	{
		m_CursorMove += 10;
		if (m_CursorMove >= 150)
		{
			m_CursorMove = 150;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_func = &GameClearScene::FadeoutUpdate;
	}
}

void GameClearScene::FadeoutUpdate()
{
	m_Color -= kFadeSpeed;

	if (m_Color <= 0)
	{
		if (m_Cursor == 0) m_PlayAgain = true;

		if (m_Cursor == 1) m_Abort = true;
	}
}
