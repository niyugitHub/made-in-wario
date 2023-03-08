#include "GameOverScene.h"
#include "Pad.h"
#include <DxLib.h>

GameOverScene::GameOverScene() : 
	m_SceneNum(0),
	m_PlayAgain(false),
	m_Abort(false),
	m_ActiveGameOver(false)
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
	m_SceneNum = 0;
	m_PlayAgain = false;
	m_Abort = false;
	m_ActiveGameOver = true;
}

void GameOverScene::Update()
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		if (m_SceneNum == 0) m_SceneNum++;

		else if (m_SceneNum == 1) m_SceneNum--;
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		if(m_SceneNum == 0) m_PlayAgain = true;

		if (m_SceneNum == 1) m_Abort = true;
	}
}

void GameOverScene::Draw()
{
//	DrawBox(0, 0, 500, 500, 0xffffff, true);

	DrawFormatString(900, 500, 0xffffff, "%d", m_SceneNum);
}
