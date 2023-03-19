#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"game.h"
#include"Pad.h"
#include"Particle.h"
#include"Option.h"
#include"cassert"

namespace
{
	// �O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphicFilename = "data/Player.png";
	const char* const kTitleFilename = "data/title.png";
	const char* const kTitleStringFilename = "data/titleString.png";
	const char* const kOptionFilename = "data/gamepad.png";

	// �T�E���h�t�@�C����
	const char* const kSoundTitleFilename = "sound/Title.mp3";

	// �J�[�\���̏����ʒu
	constexpr int kCorsolNumX = 720;
	constexpr int kCorsolNumY = 680;
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
	m_Drawfunc = &SceneTitle::FirstDraw;

	LoadDivGraph(kPlayerGraphicFilename, Player::kCharaChipNum,
		Player::kSideCharaChipNum, Player::kColumnCharaChipNum,
		Player::kSideSize, Player::kColumnSize, m_hPlayerGraphic);


	for (int i = 0; i < Player::kCharaChipNum; i++)
	{
		m_player->setHandle(i, m_hPlayerGraphic[i]);
	}

	m_TitleHandle = LoadGraph(kTitleFilename);
	m_TitleStringHandle = LoadGraph(kTitleStringFilename);
	m_OptionHandle = LoadGraph(kOptionFilename);

	m_SoundHandle = LoadSoundMem(kSoundTitleFilename);

	m_player->Init();
	m_player->SetPos(m_Pos);

	m_Particle = std::make_shared<Particle>();
	m_Option = std::make_shared<Option>();
}

SceneBase* SceneTitle::update()
{
	m_Particle->SetTitleParticle();
	m_Particle->Update();
	if (m_SceneNum == 0)
	{
		m_Cursor -= 10;
		if (m_Cursor <= 0)
		{
			m_Cursor = 0;
		}
	}

	if (m_SceneNum == 1)
	{
		m_Cursor += 10;
		if (m_Cursor >= 100)
		{
			m_Cursor = 100;
		}
	}

	if (m_Color <= 0 && m_EndScene)
	{
		StopSoundMem(m_SoundHandle);
		return (new SceneMain);
	}

	(this->*m_func)();
//	m_player->update();

	if (!CheckSoundMem(m_SoundHandle))
	{
		PlaySoundMem(m_SoundHandle, DX_PLAYTYPE_BACK);
	}

	return this;
}

void SceneTitle::draw()
{
	(this->*m_Drawfunc)();

	if (m_Option->GetActiveOption())
	{
		m_Option->Draw();
	}

	ChangeVolumeSoundMem(m_Volum,m_SoundHandle);
}

void SceneTitle::FadeinUpdate()
{
	if (m_Color <= 0)
	{
		m_Drawfunc = &SceneTitle::NormalDraw;
	}

	m_Color += 8;
	m_Volum += 8;
	if (m_Color >= 255)
	{
		m_Color = 255;
	}
	if (m_Volum >= 255)
	{
		m_Volum = 255;
	}

	if (m_Color == 255 && m_SceneNum == 0)
	{
		m_func = &SceneTitle::TitleSceneUpdate;
	}

	if (m_Color == 255 && m_SceneNum == 1)
	{
		m_func = &SceneTitle::OptionUpdate;
	}
}

void SceneTitle::TitleSceneUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_SceneNum++;
		if (m_SceneNum > 1)
		{
			m_SceneNum = 0;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_SceneNum--;
		if (m_SceneNum < 0)
		{
			m_SceneNum = 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 0)
	{
		m_IsTitleEnd = true;
		m_player->SetTitle(this);
		m_EndScene = true;
		m_func = &SceneTitle::FadeoutUpdate;
		m_Drawfunc = &SceneTitle::EndDraw;
	}

	if (Pad::isTrigger(PAD_INPUT_2) && m_SceneNum == 1)
	{
		m_Option->Init();
		m_Option->SetTitleOption(true);
		m_func = &SceneTitle::OptionUpdate;
	}
}

void SceneTitle::FadeoutUpdate()
{
	m_Color -= 9;

	if (m_EndScene)
	{
		m_Volum -= 9;
	}

	if (m_Color <= 0 && !m_EndScene)
	{
		m_func = &SceneTitle::FadeinUpdate;
	}
}

void SceneTitle::OptionUpdate()
{
	if (!m_Option->GetActiveOption())
	{
		m_func = &SceneTitle::TitleSceneUpdate;
		m_SceneNum = 0;
	}

	m_Option->Update();
}

void SceneTitle::FirstDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	DrawGraph(0, 0, m_TitleHandle, true);
	DrawGraph(0, 0, m_TitleStringHandle, true);
	m_Particle->Draw({ 0,0 });
	DrawFormatString(600, 450, GetColor(0, 0, 0), "%d", m_SceneNum);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void SceneTitle::NormalDraw()
{
	DrawGraph(0, 0, m_TitleHandle, true);
	m_Particle->Draw({0,0});

//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	if (!m_Option->GetActiveOption())
	{
		DrawGraph(0, 0, m_TitleStringHandle, true);
		DrawString(kCorsolNumX, kCorsolNumY + m_Cursor, "��", GetColor(255, 255, 255), true);
	}
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//	m_player->draw();
}

void SceneTitle::OptionDraw()
{
	DrawGraph(0, 0, m_TitleHandle, true);
	m_Particle->Draw({ 0,0 });
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	/*DrawGraph(0, 0, m_OptionHandle, true);*/

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::EndDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);
	DrawGraph(0, 0, m_TitleHandle, true);
	DrawGraph(0, 0, m_TitleStringHandle, true);
	m_Particle->TitleDraw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
