#include "SceneManager.h"
#include <cassert>
#include"SceneBase.h"
#include"SceneTitle.h"
#include"SceneMain.h"
#include"Pad.h"
#include"Option.h"
#include <DxLib.h>

namespace
{
	const char* const kGuideFilename = "data/gaido.png";
	const char* const kGuideStringFilename = "data/gaidoString.png";
}


SceneManager::SceneManager()
{
#ifdef _DEBUG
	{
		m_kind = kSceneKindMain;
	}
#else 
	{
		m_kind = kSceneKindTitle;
	}
#endif
	SetFontSize(50);
	ChangeFont("Ÿà–¾’© Light");
	m_pScene = nullptr;

	m_GuideHandle = LoadGraph(kGuideFilename);
	m_GuideStringHandle = LoadGraph(kGuideStringFilename);
	m_Option = std::make_shared<Option>(m_GuideHandle, m_GuideStringHandle);
}
SceneManager::~SceneManager()
{

}

void SceneManager::init(SceneKind kind)
{
	m_kind = kind;
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_Option->SetActivgeOption(false);
		m_pScene = new SceneTitle(m_Option);
		m_pScene->init();
		break;
	case SceneManager::kSceneKindMain:
		m_Option->SetActivgeOption(false);
		m_pScene = new SceneMain(m_Option);
		m_pScene->init();
		break;

	default:
		assert(false);
		break;
	}
	m_pScene->init();
}

void SceneManager::end()
{
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->end();
	delete m_pScene;
}

void SceneManager::update()
{
	Pad::update();
	assert(m_pScene);
	if (!m_pScene) return;

	SceneBase* pScene = m_pScene->update();
	assert(pScene);
	if (pScene != m_pScene)
	{
		m_pScene->end();
		delete m_pScene;

		m_pScene = pScene;
		m_pScene->init();
	}
}

void SceneManager::draw()
{
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->draw();

	if (m_Option->GetGuide())
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawGraph(0, 0, m_GuideHandle, true);
		DrawGraph(0, 0, m_GuideStringHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}