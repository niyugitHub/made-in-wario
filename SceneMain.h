#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Minigame1.h"

//class Player;
//class Minigame1;
//class Vec2;

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

	bool Collision();

private:
	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kCharaChipNum];

	Vec2 m_PlayerPos;
	
	// �v���C���[
	Player*m_player;

	// �}�b�v
	Minigame1* m_Map;
};
