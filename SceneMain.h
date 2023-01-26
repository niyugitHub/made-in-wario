#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"

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

	// �����蔻��
	void IsCollision();

	// �����蔻�菉����
	void isInitColl();

private:
	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kCharaChipNum];

	Vec2 m_PlayerPos;

	// �L�����N�^�[�ƃu���b�N�̏Փ˔���
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;
	
	// �v���C���[
	Player*m_player;

	// �}�b�v
	Map* m_Map;
};
