#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"Map.h"
#include <memory>

//class Player;
//class Minigame1;
//class Vec2;
class Collision;
class EnemyFactory;
class Item;

class SceneMain : public SceneBase
{
public:
	enum ItemType
	{
		kTwoJump,
		kAttackUp,
	};
public:
	static constexpr int kItemNum = 25;
	static constexpr int kStageItemNum = 5;
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	virtual void init();
	// �I������
	virtual void end();

	virtual SceneBase* update();
	virtual void draw();

	// �A�C�e���̈ʒu�̒���
	void IsItemPosition();

private:
	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kCharaChipNum];

	// �v���C���[�̃|�W�V����
	Vec2 m_PlayerPos;

	// �G�l�~�[�̃|�W�V����
	Vec2 m_EnemyPos;

	// �}�b�v�̃|�W�V����������
	Vec2 m_MapPos;

	// �A�C�e���̃|�W�V����
	Vec2 m_ItemPos;

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

	// �v���C���[�̑��݊m�F
	bool m_Exist;

	// �A�C�e���̑��݊m�F
	bool m_ItemExist[kItemNum];

	// �A�C�e���̌�
	int m_ItemNum;
	// 1�X�e�[�W���Ƃ̃A�C�e����
	int m_StageItemNum;

	// �v���C���[�̍U����
	int m_AttackPower;
	
	// �v���C���[
	std::shared_ptr<Player> m_player;

	// �}�b�v
	std::shared_ptr<Map> m_Map;

	// �����蔻��
	std::shared_ptr<Collision> m_Coll;

	// �A�C�e��
	std::shared_ptr<Item> m_Item[kItemNum];

	// �G�S��
	std::shared_ptr<EnemyFactory> m_EnemyFactory;
};
