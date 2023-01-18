#include "SceneManager.h"
#include <cassert>

#include"SceneTitle.h"
#include"SceneMain.h"


SceneManager::SceneManager()
{
	m_kind = kSceneKindTitle;
	m_pScene = nullptr;
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
		m_pScene = new SceneTitle;
		m_pScene->init();
		break;
	case SceneManager::kSceneKindMain:
		m_pScene = new SceneMain;
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
}