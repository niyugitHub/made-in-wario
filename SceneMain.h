#pragma once
#include"SceneBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	virtual void init();
	// �I������
	virtual void end();

	virtual SceneBase* update();
	virtual void draw();
};
