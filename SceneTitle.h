#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include "game.h"

class SceneTitle : public SceneBase
{
public:
//	constexpr int kMouseSize = 134;

public:
	SceneTitle()
	{
		m_isEnd = false;
	}
	virtual ~SceneTitle() {}


	virtual void init()override;
	virtual void end() override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

	virtual bool isEnd() { return m_isEnd; }

private:
	void FadeinUpdate();
	void TitleSceneUpdate();
	void FadeoutUpdate();

private:
	// �e�L�X�g�̃T�C�Y
	int m_textSize;

	// �F�̔Z��
	int m_Color;

	bool m_isEnd;

	// update���������o�֐��|�C���^
	void(SceneTitle::* m_func)();
};