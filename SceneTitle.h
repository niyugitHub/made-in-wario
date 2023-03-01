#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include "game.h"
#include "Player.h"

class SceneTitle : public SceneBase
{
public:
//	constexpr int kMouseSize = 134;

public:
	SceneTitle()
	{
		m_Pos.x = 0;
		m_Pos.y = 0;
		m_BackgroundPosX = 0;
		m_isEnd = false;
		m_IsTitleEnd = false;
		m_func = &SceneTitle::FadeinUpdate;
		m_textSize = 0;
		m_Color = 0;

		for (auto& handle : m_hPlayerGraphic)
		{
			handle = -1;
		}

		for (int i = 0; i < Player::kCharaChipNum; i++)
		{
			m_hPlayerGraphic[i] = -1;
		}

		m_player = new Player;

	}
	virtual ~SceneTitle() {}


	virtual void init()override;
	virtual void end() override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

	virtual bool isEnd() { return m_isEnd; }

	virtual bool isTitleEnd() { return m_IsTitleEnd; }

private:
	void FadeinUpdate();
	void TitleSceneUpdate();
	void FadeoutUpdate();
	void OptionUpdate();


	void NormalDraw();
	void OptionDraw();

private:
	// �v���C���[�̈ʒu
	Vec2 m_Pos;

	// �w�i��X�ʒu
	int m_BackgroundPosX;
	// �e�L�X�g�̃T�C�Y
	int m_textSize;

	// ���̃V�[����I�񂾂�
	int m_SceneNum = 0;

	// �F�̔Z��
	int m_Color;

	bool m_isEnd;

	bool m_IsTitleEnd;

	// update���������o�֐��|�C���^
	void(SceneTitle::* m_func)();

	// Draw���������o�֐��|�C���^
	void(SceneTitle::* m_Drawfunc)();

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kCharaChipNum];

	// �w�i�̃n���h��
	int m_TitleHandle = -1;
	// �w�i�̕����n���h��
	int m_TitleStringHandle = -1;

	// �I�v�V�����̃n���h��
	int m_OptionHandle = -1;

	int m_Cursor = 0;

	Player* m_player;
};