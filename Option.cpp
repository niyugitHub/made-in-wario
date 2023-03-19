#include "Option.h"
#include "Pad.h"
#include <DxLib.h>

namespace
{
	
	const char* const kOptionStringFilename = "data/optionString.png";
	const char* const kGamePadFilename = "data/gamepad.png";
	const char* const kGameEndFilename = "data/GameEnd.png";

	// カーソルの初期位置
	constexpr int kCursorNumX = 700;
	constexpr int kCursorNumY = 560;

	// フェードイン、フェードアウトの速さ
	constexpr int kFadeSpeed = 8;
}

Option::Option() : 
	m_SceneNum(0),
	m_OptionScene(false)
{
	m_StringHandle = LoadGraph(kOptionStringFilename);
	m_GamepadHandle = LoadGraph(kGamePadFilename);
	m_GameEndHandle = LoadGraph(kGameEndFilename);
	m_func = &Option::FirstUpdate;
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
	m_TitleScene = false;
	m_func = &Option::FirstUpdate;
	m_drawfunc = &Option::OptionDraw;
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
		if (m_CursorMove > 135)
		{
			m_CursorMove -= 10;

			if (m_CursorMove <= 135)
			{
				m_CursorMove = 135;
			}
		}

		if (m_CursorMove < 135)
		{
			m_CursorMove += 10;

			if (m_CursorMove >= 135)
			{
				m_CursorMove = 135;
			}
		}
	}

	if (m_SceneNum == 2)
	{
		if (m_CursorMove < 270)
		{
			m_CursorMove += 10;

			if (m_CursorMove >= 270)
			{
				m_CursorMove = 270;
			}
		}
	}
}

void Option::FirstUpdate()
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
		m_drawfunc = &Option::GamepadDraw;
		m_func = &Option::NextUpdate;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 2)
	{
		m_drawfunc = &Option::GameEndDraw;
		m_func = &Option::NextUpdate;
		m_GameCount = 0;
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_OptionScene = false;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 1)
	{
		m_OptionScene = false;
	}
}

void Option::NextUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_func = &Option::FirstUpdate;
		m_drawfunc = &Option::OptionDraw;
	}
}

//void Option::FadeinUpdate()
//{
//	m_Color += kFadeSpeed;
//	if (m_Color <= 255)
//	{
//		m_Color = 255;
//		m_func = &Option::NormalUpdate;
//	}
//}
//
//void Option::NormalUpdate()
//{
//	if (Pad::isTrigger(PAD_INPUT_DOWN))
//	{
//		m_SceneNum++;
//		
//		if (m_SceneNum > 2)
//		{
//			m_SceneNum = 0;
//		}
//	}
//
//	if (Pad::isTrigger(PAD_INPUT_UP))
//	{
//		m_SceneNum--;
//
//		if (m_SceneNum < 0)
//		{
//			m_SceneNum = 2;
//		}
//	}
//
//	CursorMove();
//
//	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 0)
//	{
//		m_func = &Option::FadeoutUpdate;
//		m_drawfunc = &Option::GamepadDraw;
//	}
//
//	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 1)
//	{
//		m_func = &Option::FadeoutUpdate;
//		m_drawfunc = &Option::StatusDraw;
//	}
//
//	if (Pad::isTrigger(PAD_INPUT_8))
//	{
//		m_func = &Option::FadeoutUpdate;
//		m_drawfunc = &Option::OptionDraw;
//	}
//}
//
//void Option::FadeoutUpdate()
//{
//	m_Color -= kFadeSpeed;
//
//	if (m_Color < 0)
//	{
//		m_func = &Option::FadeinUpdate;
//
//		if (m_SceneNum = 2)
//		{
//			m_OptionScene = false;
//		}
//	}
//}

void Option::OptionDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_OptionHandle, true);
	DrawGraph(0, 0, m_StringHandle, true);
	DrawString(kCursorNumX, kCursorNumY + m_CursorMove, "→", 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Option::GamepadDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_OptionHandle, true);

	DrawGraph(0, 0, m_GamepadHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Option::GameEndDraw()
{
	m_GameCount++;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_OptionHandle, true);
	DrawGraph(0, 0, m_GameEndHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (Pad::isTrigger(PAD_INPUT_2) && m_GameCount > 30)
	{
		m_GameEnd = true;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_GameCount > 30 && m_TitleScene)
	{
		DxLib_End();
	}
}
