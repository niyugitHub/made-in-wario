#pragma once
#include"SceneBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ‰Šú‰»
	virtual void init();
	// I—¹ˆ—
	virtual void end();

	virtual SceneBase* update();
	virtual void draw();
};
