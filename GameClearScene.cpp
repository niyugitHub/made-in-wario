#include "GameClearScene.h"
#include "Pad.h"
#include "Particle.h"
#include <DxLib.h>

namespace
{
	const char* const kGameOverSceneGraphicFilename = "data/GameOverScene.png";

	// カーソルの初期位置
	constexpr int kCursorNumX = 500;
	constexpr int kCursorNumY = 470;

	// グラフの切り替えフレーム
	constexpr int kGraphFrame = 20;

	// フェードイン、フェードアウトの速さ
	constexpr int kFadeSpeed = 8;
}

GameClearScene::GameClearScene(int handle) :
	m_handle(handle),
	/*m_GuideHandle(GuideHandle),
	m_GuideStringHandle(GuideStringHandle),*/
	m_Graph(0),
	m_GraphFrame(0),
	m_Cursor(0),
	m_CursorMove(0),
	m_PlayAgain(false),
	m_Abort(false),
	m_Color(0),
	m_Particle(std::make_shared<Particle>())
{
	for (int i = 0; i < 72; i++)
	{
		m_PlayerHandle[i] = -1;
	}
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

	m_Particle->Update();
	m_Particle->SetGameClearParticle();

	m_GraphFrame++;

	if (m_GraphFrame % kGraphFrame == 0)
	{
		m_Graph++;
		if (m_Graph >= 2)
		{
			m_Graph = 0;
		}
	}
}

void GameClearScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Color);

	m_Particle->Draw({0,0});
	DrawGraph(0, 0, m_handle, true);
	DrawString(kCursorNumX, kCursorNumY + m_CursorMove, "→", 0xffffff, true);

	DrawRotaGraph(300, 500,6.0f, 0,
		m_PlayerHandle[m_Graph],true,false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
		m_CursorMove -= 15;
		if (m_CursorMove <= 0)
		{
			m_CursorMove = 0;
		}
	}

	if (m_Cursor == 1)
	{
		m_CursorMove += 15;
		if (m_CursorMove >= 210)
		{
			m_CursorMove = 210;
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
