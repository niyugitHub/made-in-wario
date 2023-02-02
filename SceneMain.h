#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"

//class Player;
//class Minigame1;
//class Vec2;
class Collision;
class Enemy1;

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

private:
	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kCharaChipNum];

	// �v���C���[�̃|�W�V����
	Vec2 m_PlayerPos;

	// �G�l�~�[�̃|�W�V����
	Vec2 m_EnemyPos;

	// �L�����N�^�[�ƃu���b�N�̏Փ˔���
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	// �G�l�~�[�ƃu���b�N�̏Փ˔���
	bool m_CollTopEnemy;
	bool m_CollBottomEnemy;
	bool m_CollLeftEnemy;
	bool m_CollRightEnemy;

	// �v���C���[�̎��S����
	bool m_DeadPlayer;

	
	// �v���C���[
	Player*m_player;

	// �}�b�v
	Map* m_Map;

	// �����蔻��
	Collision* m_Coll;

	// �G
	Enemy1* m_Enemy;
};
