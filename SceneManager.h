#pragma once

#include"SceneBase.h"
#include<memory>

class Option;

class SceneManager
{
public:
	// ƒV[ƒ“‚Ìí—Ş’è‹`
	typedef enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
	

		//kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	void init(SceneKind kind = kSceneKindTitle);
	void end();

	void update();
	void draw();


private:
	SceneKind	m_kind;

	SceneBase* m_pScene;

	std::shared_ptr<Option> m_Option;

	int m_GuideHandle = -1;
	int m_GuideStringHandle = -1;

	//SceneTitle	m_title;
	//Scenemain	m_main;
};