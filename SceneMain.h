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
class GameOverScene;
class Option;
class SceneTitle;
class Tutorial;

class SceneMain : public SceneBase
{
//public:
//	enum ItemType
//	{
//		kTwoJump,
//		kAttackUp,
//	};
public:
	static constexpr int kItemNum = 15;
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
	void IsItemPosition(int StageNum);

	// �v���C���[�̈ʒu����
	void InitPlayerPos();

	// �`���[�g���A���V�[���Ɉړ����邩
	bool SceneTutorial();

private:
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();
	void OptionUpdate();
	void TutorialUpdate();

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

	// �}�b�v�̈ړ���
	Vec2 m_offset;

	//// �L�����N�^�[�ƃu���b�N�̏Փ˔���
	//bool m_CollTop;
	//bool m_CollBottom;
	//bool m_CollLeft;
	//bool m_CollRight;

	// �G�l�~�[�ƃu���b�N�̏Փ˔���
	bool m_CollTopEnemy;
	bool m_CollBottomEnemy;
	bool m_CollLeftEnemy;
	bool m_CollRightEnemy;

	// �v���C���[�̑��݊m�F
	bool m_Exist;

	int m_tempScreenH;

	int m_QuakeFrame = 0;
	float m_QuakeX = 0.0f;

	// �A�C�e���̑��݊m�F
	bool m_ItemExist[kItemNum];

	// �A�C�e���̌�
	int m_ItemNum;
	// 1�X�e�[�W���Ƃ̃A�C�e����
	int m_StageItemNum;

	// �v���C���[�̍U����
	int m_AttackPower;

	// ���ǂ��̃X�e�[�W���v���C���Ă��邩
	int m_Stage;

	// �w�i�̖��邳(�t�F�[�h�C���A�t�F�[�h�A�E�g���ɈÂ��Ȃ�)
	int m_Color;
	
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

	// �Q�[���I�[�o�[�V�[��
	std::shared_ptr<GameOverScene> m_GameOverScene;

	// �I�v�V�������
	std::shared_ptr< Option> m_Option;

	// �`���[�g���A��
	std::shared_ptr<Tutorial> m_Tutorial;

	// �^�C�g���V�[��
	std::shared_ptr<SceneTitle> m_SceneTitle;

	//update���������o�֐��|�C���^
	void (SceneMain::* m_func)();
};
