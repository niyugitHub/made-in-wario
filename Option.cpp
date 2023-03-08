#include "Option.h"
#include "Pad.h"
#include <DxLib.h>

namespace
{
	const char* const kOptionFilename = "data/option.png";
	const char* const kGamePadFilename = "data/gamepad.png";
//	const char* const kOptionFilename = "data/GameOverScene.png";

	// カーソルの初期位置
	constexpr int kCursorNumX = 550;
	constexpr int kCursorNumY = 600;

	// フェードイン、フェードアウトの速さ
	constexpr int kFadeSpeed = 8;
}

Option::Option() : 
	m_SceneNum(0),
	m_OptionScene(false)
{
	m_OptionHandle = LoadGraph(kOptionFilename);
	m_GamepadHandle = LoadGraph(kGamePadFilename);
	m_StatusHandle = -1;
	m_func = &Option::FadeinUpdate;
	m_drawfunc = &Option::OptionDraw;
}

Option::~Option()
{
}

void Option::Init()
{
	m_SceneNum = 0;
	m_CursorMove = 0;
	m_Color = 0;
	m_OptionScene = true;
	m_func = &Option::FadeinUpdate;
}

void Option::Update()
{
	(this->*m_func)();
}

void Option::Draw()
{
	(this->*m_drawfunc)();

	DrawFormatString(500, 500, 0xffffff, "%d", m_CursorMove);
	DrawFormatString(500, 600, 0xffffff, "%d", m_SceneNum);
}

void Option::CursorMove()
{
	if (m_SceneNum == 0)
	{
		if (m_CursorMove > 0)
		{
			m_CursorMove -= 10;

			if (m_CursorMove <= 0)
			{
				m_CursorMove = 0;
			}
		}
	}

	if (m_SceneNum == 1)
	{
		if (m_CursorMove > 100)
		{
			m_CursorMove -= 10;

			if (m_CursorMove <= 100)
			{
				m_CursorMove = 100;
			}
		}

		if (m_CursorMove < 100)
		{
			m_CursorMove += 10;

			if (m_CursorMove >= 100)
			{
				m_CursorMove = 100;
			}
		}
	}

	if (m_SceneNum == 2)
	{
		if (m_CursorMove < 200)
		{
			m_CursorMove += 10;

			if (m_CursorMove >= 200)
			{
				m_CursorMove = 200;
			}
		}
	}
}

void Option::FadeinUpdate()
{
	m_Color += kFadeSpeed;
	if (m_Color <= 255)
	{
		m_Color = 255;
		m_func = &Option::NormalUpdate;
	}
}

void Option::NormalUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_SceneNum++;
		
		if (m_SceneNum > 2)
		{
			m_SceneNum = 0;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_SceneNum--;

		if (m_SceneNum < 0)
		{
			m_SceneNum = 2;
		}
	}

	CursorMove();

	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 0)
	{
		m_func = &Option::FadeoutUpdate;
		m_drawfunc = &Option::GamepadDraw;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 1)
	{
		m_func = &Option::FadeoutUpdate;
		m_drawfunc = &Option::StatusDraw;
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_func = &Option::FadeoutUpdate;
		m_drawfunc = &Option::OptionDraw;
	}
}

void Option::FadeoutUpdate()
{
	m_Color -= kFadeSpeed;

	if (m_Color < 0)
	{
		m_func = &Option::FadeinUpdate;

		if (m_SceneNum = 2)
		{
			m_OptionScene = false;
		}
	}
}

void Option::OptionDraw()
{
	DrawGraph(0, 0, m_OptionHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	DrawString(kCursorNumX, kCursorNumY + m_CursorMove, "→", 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Option::GamepadDraw()
{
	DrawGraph(0, 0, m_OptionHandle, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	DrawGraph(0, 0, m_GamepadHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Option::StatusDraw()
{
	/*DrawGraph(0, 0, m_OptionHandle, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	DrawString(kCursorNumX, kCursorNumY + m_CursorMove, "→", 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/
}
