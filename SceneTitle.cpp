#include "DxLib.h"
#include "SceneTitle.h"
#include"game.h"

void SceneTitle::init()
{
//	m_RandColor = 0;
	m_isEnd = false;
	m_textSize = 50;
}

SceneBase* SceneTitle::update()
{
	
	return this;
}

void SceneTitle::draw()
{
	SetFontSize(50);
	DrawString(150, 200, "�e�g���X", GetColor(0, 255, 0));
	DrawString(150, 450, "SPACE�������ăX�^�[�g", GetColor(0, 255, 0));
}